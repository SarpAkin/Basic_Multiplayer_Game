import os
import sys
import ClassParser

compenent_dir = "../src/shared/EntityCompenents"

executable_dir = sys.argv[0]
executable_dir = executable_dir[0:executable_dir.rfind("/") + 1]

h_format = [".h",".hpp"]

enum_name = "compenentTypes"
base_compenent = "Compenent"
base_compenent_dir = "compenent.h"
base_compenent_dir = executable_dir + compenent_dir + "/" + base_compenent_dir

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

compenent_names = list()

all_compenents_include = ""

# Example function which is passes to parser and called when a class is parsed
def compenentSerilizer(class_,headerPath) -> str:
    # Return if the class isn't inherited form Compenent
    if( not (base_compenent in class_.inherited)):
        return ""
    
    c_h = headerPath.replace(executable_dir + compenent_dir + "/","")
    global all_compenents_include
    all_compenents_include += f"#include \"{c_h}\"\n"

    #append the compenend names which will later be used to construct a enum
    compenent_names.append(class_.typename)
    
    class_.generated += f"\npublic:"
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
    for f in serializeable:
        srcGenerated += f"\n\tm.push_back({f.variablename});"
    srcGenerated += "\n}\n"
    ##

    ##Deserialization
    srcGenerated += f"\nvoid {class_.typename}::Deserialize(Message& m)\n" + "{"

    for f in serializeable:
        srcGenerated += f"\n\t{f.variablename} = m.pop_front<{f.typename}>();"
    srcGenerated += "\n}\n"
    ##

    srcGenerated += f"\n{class_.typename}::{class_.typename}(Entity* e)"
    srcGenerated += f"\n : {class_.inherited[0]}::{class_.inherited[0]}(e)" + "\n{"
    srcGenerated += f"\n\tStart();"
    srcGenerated += "\n}\n"

    return srcGenerated  # return the generated body part or empty string


headers_files = findInDir(compenent_dir)
headers_files.remove(compenent_dir + "/compenentTypes.h")
headers_files.remove(compenent_dir + "/allCompenent.h")

for h_file in headers_files:
    source_file = h_file[:h_file.rfind(".")] + ".cpp"
    if not os.path.isfile(executable_dir + source_file):
        open(executable_dir + source_file,"w").write("\n")
    
    ClassParser.ParseClass(executable_dir + h_file,executable_dir + source_file,compenentSerilizer)

compenent_Types_enum = "#ifndef COMPENENT_TYPES_H\n#define COMPENENT_TYPES_H\n\n"
compenent_Types_enum += f"enum class {enum_name}" + "\n{\n"
for cname in compenent_names:
    compenent_Types_enum += f"{cname}_,\n"
compenent_Types_enum += "};\n#endif"
open(executable_dir + compenent_dir + "/compenentTypes.h","w").write(compenent_Types_enum)

open(executable_dir + compenent_dir + "/allCompenent.h","w").write(all_compenents_include)

def baseCompFunc(class_,h__) -> str:
    if class_.typename != base_compenent:
        return ""
    
    class_.generated += "\npublic:"
    class_.generated += f"\n\tstatic void SerializeAll(std::vector<std::unique_ptr<{base_compenent}>>&,Message&);"
    class_.generated += "\n\tstatic void DeserializeAll(Entity*,Message&)\n;"

    srcGenerated = ""

    #Serialize
    srcGenerated += f"\nvoid {base_compenent}::SerializeAll(std::vector<std::unique_ptr<{base_compenent}>>& comps,Message& m)" + "\n{"
    srcGenerated += "\n\tfor(auto& comp : comps)"
    srcGenerated += "\n\t\tcomp->Serialize(m);"
    srcGenerated += "\n}\n"

    #Deserialize
    srcGenerated += f"\nvoid {base_compenent}::DeserializeAll(Entity* e,Message& m)" + "\n{"
    srcGenerated += f"\n\twhile(m.data.size() >= sizeof({enum_name}))" + "\n\t{"
    srcGenerated += f"\n\t\tauto compType = m.pop_front<{enum_name}>();"
    srcGenerated += f"\n\t\tswitch(compType)" + "\n\t\t{"
    for c_name in compenent_names:
        srcGenerated += f"\n\t\t\tcase {enum_name}::{c_name}_:"
        srcGenerated += f"\n\t\t\te->getCompenent<{c_name}>().Deserialize(m);"
        srcGenerated += f"\n\t\t\tbreak;\n"
    srcGenerated += f"\n\t\t\tdefault:"
    srcGenerated += f"\n\t\t\tstd::cout << \"invalid compenent Type! \" << (int)compType << \'\\n\';"
    srcGenerated += f"\n\t\t\tbreak;"

    srcGenerated += "\n\t\t}"
    srcGenerated += "\n\t}"
    srcGenerated += "\n}\n"

    return srcGenerated

source_file = base_compenent_dir[:base_compenent_dir.rfind(".")] + ".cpp"
ClassParser.ParseClass(base_compenent_dir,source_file,baseCompFunc)