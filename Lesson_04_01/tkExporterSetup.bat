@echo off

@set CURRENT_DIR=%~dp0

pushd %CURRENT_DIR%

@rem maxScript���R�s�[
@copy "%CURRENT_DIR%\tkExporter.ms" "c:\Program Files\Autodesk\3ds Max 2017\scripts\"
@copy "%CURRENT_DIR%\tkExporter.ms" "c:\Program Files\Autodesk\3ds Max 2018\scripts\"
@copy "%CURRENT_DIR%\tkExporter.ms" "c:\Program Files\Autodesk\3ds Max 2019\scripts\"
@copy "%CURRENT_DIR%\tkExporter.ms" "c:\Program Files\Autodesk\3ds Max 2020\scripts\"



@popd
@echo �Z�b�g�A�b�v�I��

@pause