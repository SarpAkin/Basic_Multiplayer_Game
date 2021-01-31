import os
import sys
import json
import ClassParser

component_dir = "../src/shared/EntityComponents"

executable_dir = sys.argv[0]
executable_dir = executable_dir[0:executable_dir.rfind("/") + 1]

h_format = [".h",".hpp"]

enum_name = "componentTypes"
base_component = "Component"
base_component_dir = "component.h"
base_component_dir = executable_dir + component_dir + "/" + base_component_dir

def findInDir(path: str):
    h_files = list()
    files: list = os.listdir(executable_dir + path)
    for file in files:
        fileDir: str = path + "/" + file
        if(os.path.isdir(executable_dir + fileDir)):
            findInDir(fileDir)
        for _format in h_format:
            if(os.path.isfile(executable_dir + fileDir)):
                file_format = fileDir[-len(_format):len(fileDir)]
                if(file_format == _format):
                    h_files.append(fileDir)
    return h_files

component_cache = executable_dir + "components.json"

component_names = list()
component_names_ = list()
try:
    component_names_ = json.load(open(component_cache))["components"]
except:
    print("couldn't open json file")

all_components_include = ""

def check_intersect(a:list,b:list) -> bool:
    
    for a_ in a:
        if a_ in b:
            return True
    return False

# Example function which is passes to parser and called when a class is parsed
def componentSerilizer(class_,headerPath) -> str:
    # Return if the class isn't inherited form Component
    #if( not (base_component in class_.inherited)):
    #    return ""
    if not (check_intersect(component_names_,class_.inherited) or class_.typename == base_component):
        return ""
    
    c_h = headerPath.replace(executable_dir + component_dir + "/","")
    global all_components_include
    all_components_include += f"#include \"{c_h}\"\n"

    #append the compenend names which will later be used to construct a enum
    component_names.append(class_.typename)
    
    class_.generated += f"\nprotected:"
    class_.generated += f"\n\tvoid Serialize_(Message&);"
    class_.generated += f"\npublic:"
    if class_.typename != base_component:
        class_.generated += f"\n\t{class_.typename}(Entity*);"
        class_.generated += f"\n\tvoid Serialize(Message&) override;"
    class_.generated += f"\n\tvoid Deserialize(Message&);"
    class_.generated += f"\n\tvoid Start();"
    class_.generated += "\n"


    #serialization

    ##finding serializeable fields
    serializeable = list()
    for f in class_.variables:
        if("serializeable" in f.tags):
            serializeable.append(f)
    ##
    srcGenerated = ""

    ##Serialization
    srcGenerated += f"\nvoid {class_.typename}::Serialize(Message& m)\n" + "{"

    srcGenerated += f"\n\tm.push_back_({enum_name}::{class_.typename}_);"
    srcGenerated += f"\n\tSerialize_(m);"
    srcGenerated += "\n}\n"
    ##

    ##Serialization_
    srcGenerated += f"\nvoid {class_.typename}::Serialize_(Message& m)\n" + "{"

    #srcGenerated += f"\n\tm.push_back_({enum_name}::{class_.typename}_);"
    if class_.typename != base_component:
        srcGenerated += f"\n\t{class_.inherited[0]}::Serialize_(m);"
    for f in serializeable:
        srcGenerated += f"\n\tm.push_back({f.variablename});"
    srcGenerated += "\n}\n"
    ##

    ##Deserialization
    srcGenerated += f"\nvoid {class_.typename}::Deserialize(Message& m)\n" + "{"
    if class_.typename != base_component:
        srcGenerated += f"\n\t{class_.inherited[0]}::Deserialize(m);"
    for f in serializeable:
        srcGenerated += f"\n\tm.pop_front({f.variablename});"
    srcGenerated += "\n}\n"
    ##

    srcGenerated += f"\n{class_.typename}::{class_.typename}(Entity* e)"

    if class_.typename != base_component:
        srcGenerated += f"\n : {class_.inherited[0]}::{class_.inherited[0]}(e)" 
    srcGenerated +=  "\n{"
    if class_.typename != base_component:
        srcGenerated += "\n\tentity = e;"
    srcGenerated += f"\n\tStart();"
    srcGenerated += "\n}\n"

    return srcGenerated  # return the generated body part or empty string


headers_files = findInDir(component_dir)
headers_files.remove(component_dir + "/componentTypes.h")
headers_files.remove(component_dir + "/allComponent.h")

for h_file in headers_files:
    source_file = h_file[:h_file.rfind(".")] + ".cpp"
    if not os.path.isfile(executable_dir + source_file):
        open(executable_dir + source_file,"w").write("\n")
    
    ClassParser.ParseClass(executable_dir + h_file,executable_dir + source_file,componentSerilizer)

component_Types_enum = "#ifndef COMPENENT_TYPES_H\n#define COMPENENT_TYPES_H\n\n"
component_Types_enum += f"enum class {enum_name}" + "\n{\n"
for cname in component_names:
    component_Types_enum += f"{cname}_,\n"
component_Types_enum += "};\n#endif"
open(executable_dir + component_dir + "/componentTypes.h","w").write(component_Types_enum)

open(executable_dir + component_dir + "/allComponent.h","w").write(all_components_include)

def baseCompFunc(class_,h__) -> str:
    if class_.typename != base_component:
        return ""
    
    class_.generated += "\npublic:"
    #class_.generated += f"\n\tstatic void SerializeAll(std::vector<std::unique_ptr<{base_component}>>&,Message&);"
    class_.generated += "\n\tstatic void DeserializeAll(Entity*,Message&);\n"

    srcGenerated = componentSerilizer(class_,h__)
    component_names.pop()#remove the duplicate which is created at the previous line

    """
    #Serialize
    srcGenerated += f"\nvoid {base_component}::SerializeAll(std::vector<std::unique_ptr<{base_component}>>& comps,Message& m)" + "\n{"
    srcGenerated += "\n\tfor(auto& comp : comps)"
    srcGenerated += "\n\t\tcomp->Serialize(m);"
    srcGenerated += "\n}\n"
    """

    #Deserialize
    srcGenerated += f"\nvoid {base_component}::DeserializeAll(Entity* e,Message& m)" + "\n{"
    srcGenerated += f"\n\twhile(m.size() >= sizeof({enum_name}))" + "\n\t{"
    srcGenerated += f"\n\t\tauto compType = m.pop_front<{enum_name}>();"
    srcGenerated += f"\n\t\tswitch(compType)" + "\n\t\t{"
    for c_name in component_names:
        if c_name == base_component:
            continue
        srcGenerated += f"\n\t\t\tcase {enum_name}::{c_name}_:"
        srcGenerated += "\n\t\t\t{"
        srcGenerated += f"\n\t\t\t\tauto comp = e->getComponent<{c_name}>();"
        srcGenerated += f"\n\t\t\t\tcomp.Deserialize(m);"
        srcGenerated += f"\n\t\t\t\tcomp.OnSync();"
        srcGenerated += f"\n\t\t\t\tbreak;\n"
        srcGenerated += "\n\t\t\t}"
    srcGenerated += f"\n\t\t\tdefault:"
    srcGenerated += f"\n\t\t\tstd::cout << \"invalid component Type! \" << (int)compType << \'\\n\';"
    srcGenerated += f"\n\t\t\treturn;"
    srcGenerated += f"\n\t\t\tbreak;"

    srcGenerated += "\n\t\t}"
    srcGenerated += "\n\t}"
    srcGenerated += "\n}\n"

    return srcGenerated

source_file = base_component_dir[:base_component_dir.rfind(".")] + ".cpp"
ClassParser.ParseClass(base_component_dir,source_file,baseCompFunc)
d = dict()
d["components"] = component_names
json.dump(d,open(component_cache,"w"))