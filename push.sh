#!/bin/bash
if [[ $# -ne 2 ]]; then
    echo "Usage: ${0} msg"
fi
git add .
git commit -m ${1}
git push
