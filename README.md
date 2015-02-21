> md5 generator is tool to generate multiple md5 checksums  accross various directories.

#Command line parameters:

|                  | Description                                                                 | Default Value       |
 ----------------- | --------------------------------------------------------------------------- | ------------------
| help             | Show help                                                                   |                     |
| help-generator   | Help for generators. Possible values = [singlefile, multiplefile, trace]    |                     |
| dir              | Directories to compute hash                                                 |                     |
| file_pattern     | Pattern on which performing checksum                                        | .* | .*\.dll        |
| generator        | Name of the generator. Posible values = [file, trace]                       |                     |
| level            | Recursive level                                                             | unlimited           |


##Trace Generator dedicated options:

|                  | Description                                           | Default Value       |
 ----------------- | ---------------------------------------------------   | ------------------


##Single File Generator dedicated options:

|                  | Description                                           | Default Value       |
 ----------------- | ---------------------------------------------------   | ------------------
| output_file      | Output File                                           |                     |


##Multiple File Generator dedicated options:

|                  | Description                                           | Default Value       |
 ----------------- | ---------------------------------------------------   | ------------------


> How to build

> Boost must have been built using those flags : b2 runtime-link=static variant=debug threading=multi