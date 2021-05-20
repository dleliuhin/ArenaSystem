#!/bin/bash

# Check commit message title and description by pattern

[[ -z $1 ]] && echo -e "\e[44mEmpty arg 1 (Commit message)\e[0m" && exit 1 

bakred='\e[41m'   # Red
bakgrn='\e[42m'   # Green
txtrst='\e[0m'    # Text Reset

COMMIT_MSG_PATTERN='^(([rR]ebase|REBASE)|([hH]ot[fF]ix|HOTFIX)|([fF]ix|FIX)|([tT]est|TEST)|([fF]eature)|([Bb]ug[fF]ix|BUGFIX)|([Dd]oc)|([Rr]efactor))([\.]?\s.+)?$'

if ! echo "$1" | grep  -qE "$COMMIT_MSG_PATTERN"; then 
    echo -e "${bakred} $1 ${txtrst}"
    echo -e "${bakred}Aborting according commit message policy.${txtrst}"
    echo -e "Please specify name from following:"
    echo "REBASE/Rebase/rebase"
    echo "FIX/Fix/fix"
    echo "HOTFIX/HotFix/Hotfix/hotfix"
    echo "FEATURE/Feature/feature"
    echo "TEST/Test/test"
    echo "BUGFIX/BugFix/Bugfix/bugfix"   
    echo "Example: \n fix. message"
    exit 1 
else
    echo -e "${bakgrn}Commit message is OK.${txtrst}"
    exit 0
fi
     


