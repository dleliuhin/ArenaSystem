#!/bin/bash

# Script which find functions left in the code during debugging.

bakred='\e[41m'   # Red
bakgrn='\e[42m'   # Green
bakylw='\e[43m'   # Yellow
bakblu='\e[44m'   # Blue
txtrst='\e[0m'    # Text Reset
txtylw='\e[0;33m' # Yellow
txtcyn='\e[0;36m' # Cyan
txtred='\e[0;31m' # Redecho -e "${bakblu}Pre-commit check for debug code usage.${txtrst}"

CHECK_LIST='./src --exclude-dir=plot'

check_pattern(){
        RESULT=$(grep -RHInw "$1" ${CHECK_LIST})
        if [[ -z $RESULT ]]; then
                return 0
        else
                echo -e "${txtred}Detected in file${txtrst}\t$RESULT"
                return 1
        fi
}

pattern_summary=0
pattern_1_res=$(check_pattern "vdeb");   [[ $pattern_1_res ]] && echo $pattern_1_res && let pattern_summary+=1
pattern_2_res=$(check_pattern "vdebug"); [[ $pattern_2_res ]] && echo $pattern_2_res && let pattern_summary+=1
pattern_3_res=$(check_pattern "printf"); [[ $pattern_3_res ]] && echo $pattern_3_res && let pattern_summary+=1
pattern_4_res=$(check_pattern "VDEB");   [[ $pattern_4_res ]] && echo $pattern_4_res && let pattern_summary+=1

if [[ $pattern_summary -ne 0 ]]; then
        echo -e "${bakred}Debug code detected. Rejecting${txtrst}" && exit 1
else
        echo -e "${bakgrn}Code check for debug is OK${txtrst}"
fi
