
engine_path=$1
project_path=$PWD/..

"$engine_path\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin -Plugin="$project_path/Plugins/ExtendedLogs/ExtendedLogs.uplugin" -Package="$project_path/Saved/Build/${engine_path: -2}" -Rocket
