# Big Red Slack Button

It's a big red button that posts a message to Slack when you push it.

<img src="http://i.imgur.com/eAgqFot.jpg" width="800">
<img src="http://i.imgur.com/eRnmbCc.png" width="279">

# What You Need

## Hardware

[NodeMCU](http://nodemcu.com). I used the LoLin v3 board on AliExpress.

## Software

* [PlatformIO](http://platformio.org/) to compile and upload your code. It's Arduino code, so it should compile just fine using Arduino IDE too.
* [esptool](https://github.com/themadinventor/esptool) if the PlatformIO uploader for ESP8266 doesn't work.
* A [Slack](https://slack.com) team that doesn't mind you making a mess of their #random channel.

# Let's Build a Button

## Hardware

1. Acquire a Big Red Button.
2. Solder some jumper wires to its terminals.
3. Connect the jumpers to pin 0 and ground on your NodeMCU. Your pin numbers may differ from what's printed in silk on the board—on my LoLin v3 board, I had to use pins D3 and GND.

## Slack

1. Go to [https://YOUR-TEAM.slack.com/apps/build/custom-integration](https://YOUR-TEAM.slack.com/apps/build/custom-integration).
2. Create an Incoming Webhook and configure it to post to your channel.
3. Optional: Give your webhook a friendly name and icon, such as **Big Red Button** and 🔴.

## PlatformIO

1. Edit the constants in slack_button.ino to configure your wifi network and your Slack webhook URL.
2. [Install PlatformIO](http://platformio.org/#!/get-started).
3. Install support for NodeMCU: `platformio platforms install espressif`.

## esptool

This bit is optional. You only need to install and use esptool to upload to your NodeMCU if PlatformIO fails.

1. Clone [esptool](https://github.com/themadinventor/esptool) with `git clone git@github.com:themadinventor/esptool.git`.
2. Run `python setup.py install` inside the esptool directory to install esptool and pyserial.
3. Make sure the esptool executable is in your system $PATH.

## Upload

1. Connect your NodeMCU via USB.
2. Inside the project directory, type `platformio run` to compile the script.
3. Once the compile succeeds, type `platformio run --target upload` to upload to NodeMCU.
4. If the upload fails with PlatformIO, run `./upload.sh` to compile and upload with esptool instead.

## PUSH THE BUTTON

Just push it. You know you really want to.

But don't push it too many times or your boss will fire you.

# Shout Outs

[NodeMCU](http://nodemcu.com): If you want to connect something to the internet, this is easily the cheapest and easiest way to do it. The dev board is crazy good—and it's $4 on AliExpress for just one.

[PlatformIO](http://platformio.org/): If you're looking to write, compile, and upload Arduino scripts, PlatformIO is the best tool I have ever used. It's got an awesome interface and is much nicer to use than Arduino IDE.

# License

MIT
