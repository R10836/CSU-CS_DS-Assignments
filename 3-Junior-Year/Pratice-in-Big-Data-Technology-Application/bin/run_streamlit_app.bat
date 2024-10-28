@echo off
cd /d "%~dp0"
cd ..
cd src
streamlit run NLchat.py
pause
