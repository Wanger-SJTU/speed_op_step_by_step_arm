


adb push main /data/tmp/main
# cat sys/devices/system/cpu/cpu7/cpufreq/scaling_available_frequencies 
adb shell "cd /data/tmp/ && ./main"
