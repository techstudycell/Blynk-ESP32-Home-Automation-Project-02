# Blynk-ESP32-Home-Automation-Project-02
In this IoT project, I have shown how to make an IoT-based Home Automation project using ESP32 and the new Blynk IoT app to control an 8-channel relay module from the manual switch &amp; smartphone.
During the article, I have shown all the steps to make this Blynk home automation system.

## Tutorial Video on new Blynk ESP32 Smart Home

Video Link: https://youtu.be/LbQ6mCVGBeg

This Blynk ESP32 control smart relay has the following features:

Control home appliances with WiFi (Blynk IoT app).
Control home appliances with Blynk web dashboard.
Control home appliances with manual switches or push buttons.
Monitor real-time feedback in the Blynk IoT App.
Control appliances without WiFi from manual switches.
So, you can easily make this home automation project at home just by using a ESP32 and relay module. Or you can also use a custom-designed PCB for this project.

## Required Components:
1. ESP32 DEVKIT V1 board
2. 8-channel SPDT 5V Relay Module
3. Push Buttons or Switch

You can make this project just by using ESP32 and 8-channel relay module. But if you use PCB then you need the following components.

## Required Components for the PCB
1. ESP32 DEVKIT V1
2. TSOP1838 IR receiver (with metallic case)
3. Relays 5v (SPDT) (8 no)
4. BC547 Transistors (8 no)
5. PC817 Optocuplors (8 no)
6. 510-ohm 0.25-watt Resistor (8 no) (R1 - R8)
7. 1k 0.25-watt Resistors (10 no) (R9 - R18)
8. LED 5-mm (10 no)
9. 1N4007 Diodes (8 no) (D1 - D8)
10. Push Buttons (9 no) or Switches
11. Terminal Connectors
12. Jumper
13. 5V DC supply

## Required Software:
1. Blynk IoT (Blynk 2.0)
2. Arduino IDE

## Circuit Diagram of the ESP32 Home Automation Project
I have explained the circuit in the tutorial video.

This is the complete circuit diagram for this home automation project. I have explained the circuit in the tutorial video.

The circuit is very simple, I have used the GPIO pins D23, D22, D21, D19, D18, D5, D25 & D26 to control the 8 relays.

And the GPIO pins D13, D12, D14, D27, D33, D32, D15 & D4 are connected with Switches to control the 8 relays manually.

And the output pin of the IR Receiver is connected with GPIO D35.

I have used the INPUT_PULLUP function in Arduino IDE instead of using the pull-up resistors.

I have used a 5V 5A DC power supply.

## Control Relays Using Blynk IoT App
If the ESP32 is connected with WiFi, then you can control the home appliances from Blynk IoT App.

You also use multiple smartphones to control the appliances with Blynk IoT App. For that, you have to log in same Blynk account from all the smartphones. In this way, all smartphones will be sink to the Blynk server.

You can control, monitor the real-time status of the relays from anywhere in the world with the Blynk App.

## Control Relays Manually With Buttons or Switches
You can also control the relays from the switches or pushbuttons.

If the ESP32 is connected with Wi-Fi then you can monitor the real-time feedback in the Blynk IoT App.

Please refer to the circuit diagram to connect the pushbuttons or switches.

## Design the PCB for This Smart Home System
To make the circuit compact and give a professional look, I have designed the PCB after testing all the features of the smart relay module.

You can download the PCB Gerber file of this home automation project from the following link:
https://github.com/techstudycell/Blynk-ESP32-Home-Automation-Project-02/tree/main/PCB_Gerber

## Order the PCB from JLCPCB
After downloading the Garber file you can easily order the PCB

Visit https://jlcpcb.com/RAB and Sign in / Sign up
1. Click on the QUOTE NOW button.
2. Click on the "Add gerber file" button. Then browse and select the Gerber file you have downloaded.
3. Set the required parameter like Quantity, PCB masking color, etc.
4. After selecting all the Parameters for PCB click on SAVE TO CART button.
5. Type the Shipping Address.
6. Select the Shipping Method suitable for you.
7. Submit the order and proceed with the payment.
8. You can also track your order from the JLCPCB.com

My PCBs took 2 days to get manufactured and arrived within a week using the DHL delivery option. PCBs were well packed and the quality was really good at this affordable price.

## Solder All the Components on PCB
After that, I have soldered all the components as per the circuit diagram.

Then connect the ESP32 board with the PCB.

## Create FREE Blynk Cloud Account
For this smart house project, I have used the Blynk IoT Cloud Free plan.

Click on the following link to create a Blynk Cloud account.
https://blynk.cloud/dashboard/register

1. Enter email ID, then click on "Sign Up".
2. You will receive a verification email.
3. Click on Create Password in the email, Then set the password, click on Next.
4. Enter your first name, click on Done.
5. After that Blynk cloud dashboard will open.
6. Please refer to the following article to configure the Blynk cloud account (Create the template, datastreams, web dashboard)
https://iotcircuithub.com/blynk-iot-platform-setup-esp8266-esp32/

## Create a New Template in Blynk Cloud
First, you have to create a template in the Blynk cloud.

1. Click on New Template.
2. Enter a template name, select the hardware as ESP32, and the connection type will WiFi.
3. Then click on DONE.
4. You will get the BLYNK_TEMPLATE_ID and BLYNK_DEVICE_NAME after creating the temple.

The BLYNK_TEMPLATE_ID and BLYNK_DEVICE_NAME will be required while programming the ESP32.

## Create a Datastream in Blynk Cloud
After that, you have to create Datastreams. Here I will control 8 relays, so I have to create 8+1 Datastreams.

1. Go to the Datastreams tab.
2. Click on New Datastream and select Virtual Pin.
3. Enter a name, select the virtual pin V1, and the datatype will be Integer.
4. Then click on Create.
5. In a similar way, create 8 datastreams with virtual pin V1, V2, V3, V4, V5, V6, V7 and V8 to control 8 relays and 1 datastream with V9 to turn off all the relays together.

## Set Up Blynk Cloud Web Dashboard
Now go to the web dashboard tab.

Drag and drop 8 Switch widgets.

Go to the settings of each widget, and select a Datastream.

## Install Blynk IoT App to Configure Mobile Dashboard
1. Install the Blynk IoT app from Google Play Store or App Store. Then log in.
2. Go to Developer Mode.
3. Tap on the template that you have already made.
4. Now go to the Widget box (on the right) to add widgets.
5. Add Widgets in Blynk IoT App
6. Add 9 Button widgets from Widget Box. (9th button will turn off all the relays together)
7. Go to Button widget settings.
8. Enter the name, select Datastream, Mode will be Switch. Then exit.
10. After setting all the Buttons tap on exit.

## Program the ESP32 for this Blynk Project
First, download the code from the following link.

Click following link to Download Code
https://github.com/techstudycell/Blynk-ESP32-Home-Automation-Project-02/tree/main/Code

1. You have to keep all the 10 files in the same folder.
2. Open the.ino file in Arduino IDE.
3. In the code, you have to update the BLYNK_TEMPLATE_ID and BLYNK_DEVICE_NAME.
4. For this project, you have to install the Blynk 1.0.1 library.
5. Now select the ESP32 1.0 board and proper PORT.
6. Then upload the code to ESP32 Board.

## Update the WiFi Credentials Through OTA
After programming the ESP32, you have to update the WiFi credentials from the Blynk IoT app.

In the tutorial video, I have explained all the steps to update the WiFi credentials to ESP32 through OTA.

## Testing the PCB
After the ESP32 connects with the Blynk server, the WiFi indicator LED blinks very slowly.

Before connecting the appliances, please check whether you can control the relay from the Blynk IoT app.

## Connect the Home Appliances
Connect the 8 appliances with the relay module as per the circuit diagram.
Please take proper safety precautions while working with high voltage.

Connect 5-volt DC supply with the PCB. (I have used my old mobile charger 5V 2Amp)
Turn on the 110V/230V supply and 5V DC supply.

## Finally!! the Blynk Home Automation System Is Ready
Now you can control your home appliances in a smart way.

I hope you have liked this new Blynk home automation project. I have shared all the required information for this project.

I will really appreciate it if you share your valuable feedbacks. Also if you have any query please write in the comment section.

Thank you & Happy Learning.
