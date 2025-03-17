#pragma once
#ifndef COMMANDS_CONFIG_H
#define COMMANDS_CONFIG_H

#define TOTALCOMMANDS 11
#define MAXCOMMANDPARAMS 11

enum CommandParamLength{
    SET = 4,
    SETS = 1,
    SETP = 1,
    DATE = 6,
    TIME = 1,
    R1 = 1,
    R2 = 1,
    R3 = 1,
    R4 = 1,
    R5 = 1,
    R6 = 1
};
enum CommandParamLength commandParamLength;

char CommandList[TOTALCOMMANDS][11] = {
    "SET",
    "SETS",
    "SETIP",
    "DATE",
    "TIME",
    "R1",
    "R2",
    "R3",
    "R4",
    "R5",
    "R6"
};


#endif#pragma once
#ifndef COMMANDS_CONFIG_H
#define COMMANDS_CONFIG_H

#define TOTALCOMMANDS 11
#define MAXCOMMANDPARAMS 11

enum CommandParamLength{
    SET = 4,
    SETS = 1,
    SETP = 1,
    DATE = 6,
    TIME = 1,
    R1 = 1,
    R2 = 1,
    R3 = 1,
    R4 = 1,
    R5 = 1,
    R6 = 1
};
enum CommandParamLength commandParamLength;

char CommandList[TOTALCOMMANDS][11] = {
    "SET",
    "SETS",
    "SETIP",
    "DATE",
    "TIME",
    "R1",
    "R2",
    "R3",
    "R4",
    "R5",
    "R6"
};


#endif
