@echo off
:: Open in the current directory
cd %~dp0

:: Stage all changes
git add .

:: Prompt the user for a commit message
set /p CommitMsg="Enter your commit message: "

:: Commit the changes with the provided message
git commit -m "%CommitMsg%"

:: Push the changes to the remote repository
git push

:: Pause to show output and errors, if any
pause
