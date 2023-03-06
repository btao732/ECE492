productPath = "C:\Users\Moose\Documents\School\ECE492\API";
hppFile = "sparc.hpp";
cppFile = "sparc.cpp";

clibgen.generateLibraryDefinition(fullfile(productPath,hppFile), ...
"SupportingSourceFiles",fullfile(productPath,cppFile), ...
"OverwriteExistingDefinitionFiles",true, ...
"ReturnCArrays",false);

