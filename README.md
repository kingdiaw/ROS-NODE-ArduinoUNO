# ROSserial_pub_sub
## Testing (make sure PC host already installed with ROS)
#### Step 1: Open New Terminal, then run following command
`roscore`
#### Step 2: Open New Terminal Tab, then run following command
`rosrun rosserial_python serial_node.py /dev/ttyUSB0`
#### Step 3: (publish) Open New Terminal, then run following command
```
rostopic pub toggle_led std_msgs/UInt16 1 --once
rostopic pub toggle_led std_msgs/UInt16 0 --once
```
#### (Subscribe): Open New Terminal Tab, then run following command
`rostopic echo button_press`
