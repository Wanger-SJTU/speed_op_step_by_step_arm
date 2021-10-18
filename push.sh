
ori_path=$1

echo $ori_path

adb push $ori_path /data/main

adb shell "cd /data/ && chmod +x main && ./main"
