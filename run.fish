#!/usr/bin/env fish

swift build; or exit 1

set APP_DIR .build/PadApp.app/Contents
mkdir -p $APP_DIR/MacOS
cp .build/debug/PadApp $APP_DIR/MacOS/PadApp
cp Sources/PadApp/Info.plist $APP_DIR/Info.plist

.build/debug/PadApp
