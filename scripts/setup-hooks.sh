#!/bin/bash

# Set up pre-commit script

PRE_COMMIT=".git/hooks/pre-commit"

touch $PRE_COMMIT
chmod +x $PRE_COMMIT
echo '#!/bin/bash' > $PRE_COMMIT
echo -e "./scripts/hooks/check-debug.sh" >> $PRE_COMMIT

#---------------------------------------------------------------------------------------

# Commit mesage policy check

COMMIT_MSG=".git/hooks/commit-msg"

touch $COMMIT_MSG
chmod +x $COMMIT_MSG
echo '#!/bin/bash' > $COMMIT_MSG
echo 'MSG=$(cat .git/COMMIT_EDITMSG)' >> $COMMIT_MSG
echo -e "./scripts/hooks/check-commit-msg.sh "\"\$MSG\""" >> $COMMIT_MSG

#---------------------------------------------------------------------------------------

# Pre push full build & check

PRE_PUSH=".git/hooks/pre-push"

touch $PRE_PUSH
chmod +x $PRE_PUSH
echo '#!/bin/bash' > $PRE_PUSH
echo -e "./scripts/build.sh" >> $PRE_PUSH
echo -e "./scripts/build-gui.sh" >> $PRE_PUSH
echo -e "./scripts/sanalyze.sh" >> $PRE_PUSH
echo -e "./scripts/codestyle.sh" >> $PRE_PUSH
echo -e "./scripts/doc.sh" >> $PRE_PUSH
echo -e "./scripts/test.sh" >> $PRE_PUSH
echo -e "./scripts/danalyze.sh" >> $PRE_PUSH
echo -e "exit 0" >> $PRE_PUSH
