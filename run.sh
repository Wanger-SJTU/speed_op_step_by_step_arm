
platform=$1
ori_path=$2

if [ $platform == 'armv8a' ] 
then
    adb push $ori_path /data/main
    adb shell "cd /data/ && chmod +x main && ./main"
else
    $ori_path
fi