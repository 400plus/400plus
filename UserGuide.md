# Table Of Contents #




---


# Introduction #

## What is 400plus? ##

`400plus` is a free firmware enhancement software, which offers additional functionality and capabilities to your Canon 400D/XTi camera, in both a non-destructive, and non-permanent way. It works by loading into your camera's memory automatically upon boot-up, to enhance the native camera firmware; but is not a permanent firmware upgrade, and can easily be removed.

_It is designed specifically for the Canon 400D/XTi and will not work with other camera models._

## User Guide ##

This wiki page document will serve as the user guide for `400plus`. It is assumed in this document that the user has installed `400plus` prior to reading this guide and that it is working properly. For information about installing `400plus`, please see [FirmwareHackInstallation](FirmwareHackInstallation.md).


---


# The Menu #

## Accessing The Menu ##

To access `400plus`' menu, press the `DP` (`DIRECT PRINT`) button from within the main camera dialog; to exit `400plus`' menu, just half-press the shutter-release button. The `DP` button is located on the rear of the camera, at the left of the viewfinder, and beside the blue printer icon with a squiggly arrow line next to it.

## Navigating The Menu ##

`400plus` features a multi-page menu, where each page is dedicated to a certain task. To navigate the pages, use the front wheel (notice the '`<<`' and '`>>`' indicators at the header of the menu). There is also a method to quickly access any page: press and hold the `AV` button down, then a list of all available pages will appear; now use the front dial to select a page, and release the `AV` button to jump into it. Moreover, if the "Navigate to main" option is active (see [the settings page](#Settings_Page.md)), you can also press and immediately release the `AV` button to stay in the main page; once there, just use `UP` (`ISO`) and `DOWN` (`WB`) to select a page, and `SET` to enter it.

To navigate within a page, use the `UP` and `DOWN` buttons, (or `ZOOM IN` and `ZOOM OUT`, to move faster); then use the `LEFT` (`METERING`) and `RIGHT` (`AF`) buttons to change the value of the selected item (hold these buttons down to change the value faster). Items with an exclamation mark '`!`' at the left perform an action: activate it with the `SET` button. And Items with a right sign '`>`' are sub-menus: enter them with the `RIGHT` button, and return back to the main page with the `AV` button. Notice that some items can both perform an action and have a sub-menu.

## Menu Pages ##

### Parameters Page ###

This page contains extensions to the camera's shooting parameters, and also provides a quick access to some commonly-used, but hard to reach, custom functions.

|_**Item**_|_**Description**_|
|:---------|:----------------|
|Av comp|[Extended Exposure Compensation](#Extended_Exposure_Compensation.md)|
|AEB|[Extended Exposure Compensation](#Extended_Exposure_Compensation.md)|
|Color Temp. (K)|[Custom White Balance](#Custom_White_Balance.md)|
|Named Color Temps.|[Named Color Temperatures](#Named_Color_Temperatures.md)|
|AutoISO|[AutoISO](#AutoISO.md)|
|ISO|[Extended ISOs](#Extended_ISOs.md)|
|Safety Shift|[Safety Shift](#Safety_Shift.md)|
|Mirror Lockup|[Other Shortcuts](#Other_Shortcuts.md)|
|IR remote enable|[IR Settings](#IR_Settings.md)|
|Flash > Disable flash|[Flash Configuration](#Flash_Configuration.md)|
|Flash > AF Flash|[Other Shortcuts](#Other_Shortcuts.md)|
|Flash > Flash 2curt|[Other Shortcuts](#Other_Shortcuts.md)|

### Scripts Page ###

Scripts are little programs that control your camera, and automate certain tasks.

|_**Item**_|_**Description**_|
|:---------|:----------------|
|Extended AEB|[The Extended AEB Script](#Extended_AEB.md)|
|Flash AEB|[The Flash AEB Script](#Flash_AEB.md)|
|Aperture AEB|[The Aperture AEB Script](#Aperture_AEB.md)|
|ISO AEB|[The ISO AEB Script](#ISO_AEB.md)|
|Intervalometer|[The Intervalometer](#Intervalometer.md)|
|Bulb ramping|[Bulb Ramping](#Bulb_Ramping.md)|
|Handwaving|[The Hand Waving Script](#Hand_Waving.md)|
|Self-Timer|[The Self-Timer](#Self_Timer.md)|
|Long exposures|[The Long Exposure Script](#Long_Exposure.md)|
|DOF Calculator|[The DOF Calculator](#DOF_Calculator.md)|

### Info Page ###

This page contains some useful information about your camera and `400plus`.

|_**Item**_|_**Description**_|
|:---------|:----------------|
|Version|The version number of the `400plus` software currently installed.|
|Release count|The total number of shots (actuations) made by this camera body.|
|Body ID|The "BodyID" of the camera body (an internal number, unique to each camera).|
|Firmware|The firmware version (should be 1.1.1 for `400plus` to be working).|
|Owner|The owner of this camera (use Canon software to change it).|

### Settings Page ###

Some advanced settings about your camera and `400plus`; please, see [Configuration](#Configuration.md) for more information.

|_**Item**_|_**Description**_|
|:---------|:----------------|
|Language|[Internationalization](#Internationalization.md)|
|Digital ISO step|[Configuring Extended ISOs](#Configuring_Extended_ISOs.md)|
|Persist AEB|[Persisting AEB](#Persisting_AEB.md)|
|Restore config.|[Restore Configuration](#Restore_Configuration.md)|
|Config. Scripts|[Configuring Scripts](#Configuring_Scripts.md)|
|Config. Buttons|[Configuring Buttons](#Configuring_Scripts.md)|
|Config. Custom modes|[Configuring Custom Modes](#Configuring_Custom_Modes.md)|
|Config. Quick exposure|[Configuring Quick Exposure](#Configuring_Quick_Exposure.md)|
|Config. Menus|[Configuring Menus](#Configuring_Menus.md)|
|Config. Pages|[Configuring Pages](#Configuring_Pages.md)|
|Developers menu|[Developers Page](#Developers_Page.md)|

### Custom Modes Page ###

Custom modes are complete configurations of your camera, quickly accessible from the main dial; see [Custom Modes](#Custom_Modes.md) below for more information.

### Developers Page ###

_This Page Is Intentionally Left Blank._

_**Note**_: The developers page is disabled by default, and must be enabled in the [settings page](#Settings_Page.md) prior to accessing it; moreover, the developers' page lays outside the normal page navigation: press the `TRASH` button while in the menu to enter the developers' page.

_**Warning**_: The options contained in this page should be used with great care; there is probably little to see here, unless you are developing your own version of this hack.

## Personalizing The Menu ##

While in any page within the menu, you have the ability to change the order of the items to your own personal preference. To do this, just press the `PLAY` button to 'grab' an item (a small '`>`' will be displayed at the left of the item). Now use the `UP` and `DOWN` buttons to position the item where you would like it to reside (you will see the item actually move to the new position). Finish the process by pressing the `PLAY` button again, to save your changes.


---


# Enhancements And Extensions #

These are the enhancements and extensions that `400plus` provides.

## Safety Shift ##

Safety shift is a nice feature from our camera, used to avoid under/over-exposures in `Tv` and `Av` modes, when the metered exposure exceeds the limits of the lens and/or the camera.

In `Tv` mode, the camera will lower the shutter speed set by the user, when the scene require an aperture larger than the lens can provide; and it will raise the shutter speed set by the user, when the scene requires an aperture smaller than the lens can provide. In `Av` mode, safety shift will override the aperture set by the user, when the scene requires a shutter speed out of the range provided by the camera.

Safety shift is controlled with the "Safety Shift" switch in the [parameters page](#Parameters_Page.md) at [the menu](#The_Menu.md).

## Spot Metering Mode ##

The spot metering mode is similar to the _standard_ partial metering mode, but the area included in the metering is smaller (approx. 3.5% of the center of the viewfinder, vs. partial metering at approx. 9% of the center of the viewfinder). It works quite well when needed.

To enable the spot metering mode, enter the metering mode selection dialog (press the `METERING` button from the main dialog) and then press `DP`; enter that dialog again, and select any other metering mode, to disable the spot metering mode.

## Custom White Balance ##

The custom white balance option uses the color temperature configured in the "Color Temp. (K)" item from the [parameters page](#Parameters_Page.md) at [the menu](#The_Menu.md) (notice also that changing that value in the menu also sets the white balance to custom, automatically).

To enable the custom white balance, enter the white balance selection dialog (press the `WB` button from the main dialog) and then press `DP`; enter that dialog again, and select any other white balance, to disable the custom white balance.

## Named Color Temperatures ##

The named color temperatures menu extends the functionality of the custom white balance menu: instead of having to remember several color temperatures for different situations, you can store up to sixteen values here, and assign a name to each one. To set one of the available color temperatures, just press `SET`; use `RIGHT` and `LEFT` to change its value, and `JUMP` to rename it.

_**Note**_: Default names for the named color temperatures are assigned the first time you enter this menu, using the language configured in `400plus` at that moment; you will probably want to set the language before entering this menu for the first time.

## AF-Pattern Selection ##

`400plus` offers a range of additional AF-Pattern selections, instead of just the two (Manual AF point selection, and Automatic AF point selection) which are included standard in the camera. These additional AF-Pattern selections provide a wide range of multi-point selection patterns, using different combinations of the 9 focus points, for some creative AF capabilities.

To use the additional AF-Pattern selections during shooting, press the `ZOOM IN` button to enter the standard "AF-Point Selection" dialog, then press the `ZOOM IN` button again to enter the new "AF-Pattern Selection" dialog. Use the `UP`, `DOWN`, `LEFT`, `RIGHT`, and `SET` buttons there to move around the different AF-Patterns available. Half-press the shutter-release button to exit the dialog.

## Extended Exposure Compensation ##

On the [parameters page](#Parameters_Page.md) at [the menu](#The_Menu.md), `400plus` allows to override the default ±2EV limit up to ±6EV on the following parameters:

|_**Item**_|_**Parameter**_|
|:---------|:--------------|
|Av comp|Standard exposure compensation|
|AEB|Separation for the auto exposure bracketing|
|Flash comp|Flash exposure compensation|

## Flash Configuration ##

Flash can be completely disabled, and it will not fire even if has been raised, using the "Flash" > "Disable flash" option in the [parameters page](#Parameters_Page.md) at [the menu](#The_Menu.md).

## Extended ISOs ##

Extended (or intermediate) ISOs allow for finer-grained (1/8 EV) control of the ISO parameter for the creative modes.

Extended ISOs are available at the "ISO" item in the [parameters page](#Parameters_Page.md) at [the menu](#The_Menu.md); you can also use extended ISOs with the `TRASH` or `JUMP` buttons, if configured (see [configuring buttons](#Configuring_Buttons.md)).

### Configuring Extended ISOs ###

The "Digital ISO step" entry in the [settings page](#Settings_Page.md) at [the menu](#The_Menu.md) controls the size of the step ("1/8 EV", "1/4 EV", or "1/2 EV") used by `400plus` for extended ISOs.

### Some notes about extended ISOs ###

  * When using extended ISOs, the camera will not always display the correct ISO value; for example, an image shot at `ISO-3000` will show as `ISO-3200` during the review. This is a limitation of the original firmware.

  * _Non-standard_ ISO values are software-only calculated values, and technically offer little to no gain over shooting at the standard _base_ ISO values and later post-processing the image. They can be useful, however, when there is no time for any post-processing.

  * The _missing_ `ISO-3200`. Previous versions of `400plus` supported `ISO-3200`; or more precisely, it _appeared_ to support it: while the camera displayed "`3200`" as the ISO value, images where actually being shot at `ISO-3000`. Recent versions of `400plus` correct this bug, and only values up to `ISO-3000` are supported now. Note, thus, that _an image shot at the 'new' `ISO-3000` will be exactly the same as if shot with the 'old' `ISO-3200`_.

## AutoISO ##

`400plus` has support for AutoISO in creative modes, using our own algorithms. It works by reading the measurements that the camera makes, when you half-press the shutter button, and changing the ISO value accordingly. The behavior of AutoISO is different for each creative mode, but the idea is roughly the same: use the lowest possible ISO to maintain a suitable speed or aperture.

To enable AutoISO, enter the ISO selection dialog (press the `ISO` button from the main dialog) and then press `DP`; enter that dialog again, and select any other ISO value, to disable AutoISO. Alternatively, AutoISO can be configured in the "AutoISO" sub-menu in the [parameters page](#Parameters_Page.md) at [the menu](#The_Menu.md):

|_**Item**_|_**Description**_|
|:---------|:----------------|
|Enabled|When active (set to "Yes"), AutoISO is enabled.|
|Min ISO|Minimum ISO value that AutoISO will use.|
|Max ISO|Maximum ISO value that AutoISO will use.|
|Min Tv|Minimum shutter speed that AutoISO will try to maintain.|
|Max Av|Maximum aperture (relative to maximum aperture supported by the lens) that AutoISO will try to maintain.|
|Relaxed|When active (set to "Yes"), AutoISO in M mode will allow larger exposure deviations.|

### AutoISO In `Av` mode ###

The intention of AutoISO in `Av` mode is to use the lowest possible ISO that ensures no motion blur.

In normal `Av` mode, the user selects ISO and aperture, and the camera decides the shutter speed according to the scene. But when AutoISO is active, `400plus` will always try to use the lowest possible ISO value (as configured by "Min ISO"), unless the shutter speed gets too low (as configured by "Min Tv"); when that happens, `400plus` will automatically raise the ISO value (up to "Max ISO") as needed.

Please, note that when both Safety Shift and AutoISO are enabled, the camera could drop shutter speed below the configured "Min Tv", if "Max ISO" is reached, in order to maintain a correct exposure.

### AutoISO In `Tv` mode ###

In `Tv` mode, the intention of AutoISO is to use the lowest possible ISO that ensures an acceptable depth of field.

In `Tv` mode, AutoISO will try to keep ISO as low as possible (as configured by "Min ISO"), unless the scene requires an aperture larger than desired (as configured at "Max Av"); then, AutoISO will raise the ISO value (up to "Max ISO") as needed.

Please, note that the "Max Av" parameter is the _difference_ between the maximum aperture supported by your lens and the maximum aperture that AutoISO will allow before raising the ISO value: for example, on a f/4 lens, setting "Max Av" to +1EV means that AutoISO should raise the ISO whenever the camera sets an aperture of f/5.6 or greater. On a zoom lens with a variable maximum aperture, "Max Av" is always based on the maximum aperture supported by your lens at each moment.

In `Tv` mode, it is perfectly possible to combine both Safety Shift and AutoISO at the same time: when AutoISO can no longer increase the ISO value, the camera will use a larger aperture, and when the lens' maximum aperture is reached, Safety Shift will force a longer exposure time.

### AutoISO In `P` mode ###

In `P` mode, AutoISO _tries_ to behave just like in `Av` mode, and will raise the ISO value to keep a minimum shutter speed; but, as the camera decides both aperture and shutter speed in this mode, there is no guarantee that raising the ISO will increase shutter speed: it tends to work correctly for small values of "Min Tv", but for larger values the camera usually decides to close the diaphragm instead of selecting a faster shutter speed.

### AutoISO In `M` mode ###

In `M` mode, the behavior of AutoISO is completely different to other modes: in this case, the user selects both the aperture and the shutter speed, and `400plus` will set the most suitable ISO value to match the scene.

If the "Relaxed" parameter is active (set to "Yes"), AutoISO will allow larger exposure deviations (±2EV), before raising or lowering the ISO value, instead of the default ±1EV. Use this option if you plan to use advanced metering techniques, such as the [zone system](http://en.wikipedia.org/wiki/Zone_System).

You can change the exposure compensation in `M` mode, if the "Use D-Pad" option is active (set to "Yes"), using the `LEFT` and `RIGHT` keys while looking through the viewfinder.

If you change the exposure time up to the `BULB` mode while AutoISO is active, your camera will emit a short beep, and `400plus` will disable AutoISO, and set the ISO parameter to a fixed value of 100.

## ISO In Viewfinder ##

When the "Use D-Pad" option is active (set to "Yes"), and if the camera is set in any creative mode, you can change the ISO value while looking through the viewfinder:

  * Set the camera to `M` or `Tv` mode.
  * Look through the viewfinder, and half-press the shutter button; you should see the current measurements (shutter speed, aperture...).
  * Now press the `LEFT` and `RIGHT` buttons to change the ISO value (or `UP` just to display it); while the button is kept pressed down, the new value will be displayed in the viewfinder, in the same place where shutter speed is normally shown.

In `P` and `Av` modes, ISO can also be changed through the viewfinder, but its value is displayed in the "burst counter" (the single-digit number, at the far right of your viewfinder, that shows the number of shots remaining for a burst), using the following codes:

|_**Burst counter**_|_**ISO value**_|
|:------------------|:--------------|
|1 | 100|
|2 | 200|
|4 | 400|
|8 | 800|
|9 |1600|

_**Note**_: When custom function "_01 - SET button/Cross keys funct._" is set to "_4 : Cross keys:AF frame Selec._", this feature will remain disabled.

## Fixed exposure for `M` mode ##

While in `M` mode, `400plus` allows you to 'fix' the exposure to a certain value, and keep it stable even if you change the aperture or the exposure time: when you change on of those two values, `400plus` will automatically change the other one, in the opposite direction.

For example, suppose you set the camera to 1/100s and f/4.0 and then activate this feature. Now, if you change the exposure time to 1/50s, the aperture will jump to f/5.6; and if you change the aperture to f/2.8, the shutter speed will jump to 1/200s.

To use this feature, the "Use D-Pad" option must be active (set to "Yes"); then, look through the viewfinder and press the `SET` button. A small "`#`" symbol will be shown on the main display, just between the shutter speed and the aperture, to indicate that the feature is active. To deactivate it, just press `SET` again while looking through the viewfinder.

_**Note**_: When setting the shutter speed to `BULB`, changing to another exposure mode other than `M`, or switching the camera off, `400plus` will automatically disable this feature.

## Quick exposure for `M` mode ##

The Quick Exposure for `M` mode is intended to help you to find a 'good enough' exposure while in `M` mode; this feature is just like giving a quick peek into `P` mode.

To use this feature, the "Use D-Pad" option must be active (set to "Yes"); then, look through the viewfinder and press the `DOWN` button. Notice how the exposure and aperture change, and how the exposure indicator (both in the main display and the viewfinder) shows now a value of 0 EV.

For technical reasons, the camera must be `measuring` for Quick Exposure to work; just ensure that the viewfinder is active (half-press the shutter button otherwise) previous to using this feature.

Once Quick Exposure has set an exposure time and an aperture, you are free to change those parameters to meet your needs.

### Configuring Quick Exposure ###

There are some configuration options at the "Config. Quick Exposure" item in the [settings page](#Settings_Page.md) at [the menu](#The_Menu.md):

|_**Item**_|_**Description**_|
|:---------|:----------------|
|Min. Tv|Minimum shutter speed targeted|
|Weighting|Weighting method used|

As long as there is enough light in the scene, Quick Exposure will maintain an exposure time shorter than the "Min. Tv" value. But on low light conditions, when even opening the diaphragm to its widest aperture is not enough, Quick Exposure will use longer exposure times to avoid underexposure. Ideally, you might want to set "Min. Tv" to a value around 1 divided by the focal length of your lens.

On bright scenes, the "Weighting" functions controls which exposure parameter (from shutter speed and diaphragm aperture) must be favored to adjust the exposure. When this parameter is set to "Tv", Quick Exposure will tend to use shorter exposure times; use this value for action scenes, for example. When this parameter is set to "Av", Quick Exposure will tend to use smaller apertures; use this value to achieve a greater depth of field. Finally, when set to "None", Quick Exposure will balance between using shorter exposures and smaller apertures.

## Multi-spot metering ##

Multi-spot metering is best explained in this [guide from Canon](http://www.learn.usa.canon.com/resources/articles/2011/multispot_metering_markiii_cameras_article.htmlp); basically, it allows you to take more than one metering for a scene, and take a photograph using the average exposure. Multi-spot metering is always active, and does not need to be explicitly enabled by the user, but in only works in `P`, `Tv`, and `Av` modes. The "Use D-Pad" option must be active (set to "Yes") to use this feature.

To use multi-spot metering, follow this procedure:

  * Set the camera to one of `P`, `Tv`, `Av` modes.
  * Look through the viewfinder, and take a measurement (just half-press the shutter button, so the viewfinder lights up).
  * Now, while looking through the viewfinder, press the `DOWN` button; you'll hear a beep, and `400plus` will register that measurement.
  * Repeat this procedure to add as many readings as you need; after each reading is registered, the "burst counter" in the view finder will display the number of readings registered (notice that, while the counter has a upper limit of 9, `400plus' does not have a limit on the number of readings you can register).
  * If you want to delete the last reading, just press the `DOWN` button and hold it for two seconds; you'll hear another beep confirming the delete.
  * Once you have taken enough readings, press the `SET` button (keep looking through the viewfinder); `400plus` will set your camera to `M` mode, with the aperture and shutter speed set to the average of the apertures and shutter speeds from the readings registered.
  * Take a photograph, and `400plus` will automatically revert back to the `P` / `Av` / `Tv` mode you where using.

## RAW Support For Scene Modes ##

While in one of the scene modes, use the `AV` button to toggle between the following image type settings: `JPEG`, `RAW`, and `JPEG+RAW`. Notice that quality and size are changed to "HIGH+L" each time this option is used, by requirements of the original firmware.

## IR Settings ##

There are also some settings related to an infrared remote controller in the [parameters page](#Parameters_Page.md) at [the menu](#The_Menu.md):

|_**Item**_|_**Description**_|
|:---------|:----------------|
|IR remote enable|When active (set to "Yes"), will allow the use of an IR remote; when set to "No", camera will ignore an IR remote.|

_**Note:**_ Due to a technical limitation, the camera cannot lock the mirror up while using an infrared remote controller; thus `400plus` will disable the MLU custom function when an IR remote is active.

## Other Shortcuts ##

For your convenience, the [parameters page](#Parameters_Page.md) at [the menu](#The_Menu.md) also provides several shortcuts to some commonly-used, but hard to reach, custom functions:

|_**Item**_|_**C.Fn**_|
|:---------|:---------|
|Mirror Lockup|07|
|AF Flash|05|
|Flash 2curt|09|

While the camera is displaying the main dialog, `400plus` can assign special actions to the (otherwise unused) `JUMP` and `TRASH` buttons; please, see [the button configuration](#Configuring_Buttons.md) section for more information.

## Standard Initialization ##

To temporarily switch `400plus` completely off (for example, if you believe `400plus` is making your camera act weird), just press the `TRASH` button while the camera is powering on; the blue LED will not flash, and the camera will act as if `400plus` had never been installed. Notice that this change is not permanent, and you must hold the `TRASH` button each time the camera powers on, even when waking up from an automatic power off.

# The scripts #

To launch a script, just select it in the [scripts page](#Scripts_Page.md) at [the menu](#The_Menu.md) and press `SET` (unfortunately, scripts _still_ cannot be launched using the shutter-release button). When a script starts or stops, a _beep_ will be heard; and while a script is running, the `DP` button will flash (approx. twice per second, by default). To stop a running script, press the `DP` button again; sometimes the camera may not stop immediately, so hold the `DP` button until you hear a _beep_ that signals the effective end of the script.

You can also pause a running script, by means of simply pressing the DISP button: this will put the camera into a low-power mode, and effectively stop all ongoing activity; press DISP again, to bring back the camera into life, and the script will continue normally. All scripts will check the card capacity before each shot; if the estimated number of shots available is lower than a fixed value (3), the scripts will stop executing.

## Extended AEB ##

This script performs the same task as the _standard_ AEB option from the camera, but with a few nice enhancements:
  * Up to 9 shots may be specified.
  * The separation between shots is configurable up to ±6 EV.
  * The camera will take all the shots in a sequence, automatically.
  * User can specify the _direction_ of the sequence.

To configure and launch the Extended AEB script, use the "Ext. AEB" sub-menu in the [scripts page](#Scripts_Page.md) at [the menu](#The_Menu.md):

|_**Parameter**_|_**Description**_|
|:--------------|:----------------|
|Delay|Select whether this script should start shooting immediately or wait for 2 seconds.|
|Frames|The number of frames (shots) the script should take. Values range from 1 to 9.|
|Step (EV)|The separation in EV (exposure value) between each frame (shot). Values range from +1/3EV to +6EV.|
|Direction|Specifies the _direction_ of the EAEB sequence.|
|Bulb min|The minimum shutter speed in `BULB` mode. Values range from 1/4000th of a second to 32 minutes.|
|Bulb max|The maximum shutter speed in `BULB` mode. Values range from 1/4000th of a second to 32 minutes.|

Supposing a configuration of 5 shots at 1EV separation, this is how each _direction_ is supposed to work:

|_**Value**_|_**Meaning**_|
|:----------|:------------|
|`+/-`|One photo at current EV, and the rest above and below it: 0EV, +1EV, -1EV, +2EV, -2EV.|
|` + `|One photo at current EV, and the rest above it: 0EV, +1EV, +2EV, +3EV, +4EV.|
|` - `|One photo at current EV, and the rest below it: 0EV, -1EV, -2EV, -3EV, -4EV.|

**_Note:_**

Previous versions of this script just adjusted the EV compensation between shots; this method has one major drawback: if the light in the scene changes during the sequence, the camera may change the exposure settings between shots, and this script will end applying different compensations to unrelated exposures; the final result is not what the user would expect.

Newer versions fire the first shot without changing any parameter, but the settings used by camera get recorded; then, the camera is set into `M` mode, and the rest of the sequence is taken using parameters calculated by this script. This ensures a correct sequence, regardless of changes in the scene; but has one inconvenience: some computer programs that detect sequences of AEB shots get confused, and the images do not seem to be related at all.

### Extended AEB In `BULB` mode ###

In 'M' mode with the shutter speed set to `BULB`, this script will fire the camera as many times as needed (in this mode, the number of shots configured is irrelevant), with shutter speeds ranging from the "Bulb min:" value to the "Bulb max:" value, separating each shot by 1EV (in this mode, the separation configured is irrelevant).

Notice also that exposure times as long as 32 minutes can be used in this mode.

## Flash AEB ##

Similar to the [Extended AEB](#Extended_AEB.md) script, but only the flash exposure compensation will change.

## Aperture AEB ##

Similar to the [Extended AEB](#Extended_AEB.md) script too, and also called [depth-of-field bracketing](http://en.wikipedia.org/wiki/Bracketing#Depth-of-field_bracketing); in this case, the script changes both the aperture and shutter speed at the same time, but in different directions to maintain a constant exposure.

## ISO AEB ##

Camera will make a photograph for each ISO active. You probably want to set the camera to `M` mode prior to using this script.

## Intervalometer ##

This script will fire the camera as many times as configured (or endlessly), with a configurable delay between shots; use this script to create _stop-motion_ movies, for example. To configure and launch the Intervalometer, use the "Interval" sub-menu in the [scripts page](#Scripts_Page.md) at [the menu](#The_Menu.md):

|_**Parameter**_|_**Description**_|
|:--------------|:----------------|
|Delay|Select whether this script should start shooting immediately or wait for 2 seconds.|
|Interval|The interval time (in hours:minutes:seconds) between each shot (or group of shots); values range from 0:00:01 to 5:00:00.|
|Action|See [Script Chaining](#Script_Chaining.md).|
|Shots|The total number of frames (shots) the script will take; values range from 1 to 9000, and also include a "No Limit" value to shoot endlessly.|
|Video format (fps)|Intended playback frame-rate, if preparing a time-lapse.|
|Recording time|Estimated time that the camera will need to record the entire time-lapse (informative only).|
|Playback time|Estimated playback time of the resulting time-lapse (informative only).|

### Strict scheduling ###

Notice that `400plus` will always try to maintain a constant cadence of shots, independent of the exposure time: if configured to shot at 15s intervals, for example, then one shot will be taken exactly every 15s, even if the exposure is 10s. If one shot in the sequence has an exposure time longer than the configured interval time, `400plus` will skip as many shots as needed and reschedule the sequence accordingly. This comment is also true when the intervalometer is configured to fire any multi-shot action.

For example, imagine an interval of 5 seconds, and exposures ranging between 1 and 4 seconds (let's suppose camera is in Av mode, and light conditions change during the script):

```
Time (s) : # · · · · # · · · · # · · · · # · · · ·
Exposure : * *       * * * *   *         * *
```

Notice how the length of the pause between the end of an exposure and the beginning of the next one adapts to the exposure time, so photographs always start at regular intervals. Now, imagine that one of the exposures takes longer than 5 seconds (let's say 7):

```
Time (s) : # · · · · # · · · · # · · · · # · · · ·
Exposure : * *       * * * * * * *       * *
```

Notice that the third photograph does not take place 5 seconds after the second one, but at second 15.

_**Note**_: `400plus` will not validate that the values introduced by the user make sense at all: it will not complain if you set an interval time of 10 seconds with and exposure time of 15 seconds, for example; it is the sole responsibility of the user to avoid these situations.

### Time-lapse calculator ###

If you plan to make a time-lapse movie with the photographs taken with this script, you can specify a desired reproduction frame-rate, and the script will calculate the resulting reproduction time. These parameters are purely informative, and have no influence on the script.

## Bulb ramping ##

The bulb ramping script is similar to the intervalometer, but with the added peculiarities that it is used for long exposures (1s and longer) only, and that `400plus` will gradually change the exposure time and / or the duration of the interval between shots. Bulb ramping is used mostly to make time-lapses in situations when the amount of light is expected to change, such as sunsets.

|_**Parameter**_|_**Description**_|
|:--------------|:----------------|
|Delay|Select whether this script should start shooting immediately or wait for 2 seconds.|
|Shots|The total number of frames (shots) the script will take; values range from 1 to 9000, and also include a "No Limit" value to shoot endlessly.|
|Interval|The initial interval time (in hours:minutes:seconds) between each shot; values range from 0:00:01 to 5:00:00.|
|Exposure|The length (in minutes:seconds) of the first exposure; values range from 00:00:01 to 05:00:00.|
|Ramp size (time)|The length (in minutes:seconds) of the ramp; values range from 00:00:01 to 05:00:00.|
|Ramp size (shots)|The length (in number of shots) of the ramp; values range from 0 to 9000.|
|Ramping (interval)|The strength (in EV stops) of the ramp, as applied to the interval time; values range from -6 to +6.|
|Ramping (exposure)|The strength (in EV stops) of the ramp, as applied to the exposure time; values range from -6 to +6.|

Just as the intervalomenter, when the bulb ramping script is started, the camera will take a first shot (its length configured by "Exposure"), then a pause will follow (its length configured by "Interval"), and back to the beginning until the limit set by "Shots" is reached; but as the execution of the bulb ramping continues, the length of both the exposure and the pause between exposures will change smoothly, acording to the other parameters.

For example, if "Ramp size (shots)" is set to 5 shots, and "Ramping (exposure)" to +1EV, then the length of the exposure will double for every five shots taken; or, if "Ramp size (time)" is set to 1 hour, and "Ramping (exposure)" is set to -1EV, then the length of the interval between shots will half for every hour that the script has been running.

Notice that these changes happen gradually, there is never an abrupt change in exposure time or interval length. And also notice that there is one single ramp size, determined by the combination of "Ramp size (shots)" and "Ramp size (time)"; that ramp size is used to alter both the exposure time and the interval between shots, with a strength determined by their respective parameters.

_**Note**:_ It is quite easy to configure the script with an impossible set of parameters, or with a set of parameters that will quickly degrade to an impossible to meet schedule. If the script detects that the interval between two shot or the length of an exposure are too short, it will produce a beeping sound. If the interval or the exposure are too long, the script will stop.

## Hand Waving ##

This script will fire the camera when the display-off sensor (at the rear of the camera) is triggered. Use this script to fire the camera without the need of a remote to help reduce camera shake. If the "Repeat" option is active, this script will not end after being triggered, but will repeat itself again so you can take more shots. By default, this script will wait until something (like your hand or finger) blocks the sensor and is then removed to fire the camera. However, if the "Instant" option is enabled, the script will fire the camera as soon as the sensor becomes blocked.

To configure and launch the Hand Waving Script, use the "Handwave" sub-menu in the [scripts page](#Scripts_Page.md) at [the menu](#The_Menu.md):

|_**Parameter**_|_**Description**_|
|:--------------|:----------------|
|Delay|Select whether this script should take the shot immediately or wait for 2 seconds.|
|Action|See [Script Chaining](#Script_Chaining.md).|
|Repeat|If active (set to "Yes"), the script will restart itself after is has completed. This allows you to wave your hand repeatedly to continue using the script.|
|Instant|If selected (set to "Yes"), the script will take a shot as soon as a hand is detected; otherwise, the script will wait until the hand is removed.|

## Self Timer ##

This script simply adds a configurable pause before firing the camera.

|_**Parameter**_|_**Description**_|
|:--------------|:----------------|
|Delay|Time (in hours:minutes:seconds) that the script should wait before shooting; values range from 0:00:00 to 5:00:00.|
|Action|See [Script Chaining](#Script_Chaining.md).|

## Long Exposure ##

Just that, a configurable long exposure, from 1 seconds to 5 hours.

|_**Parameter**_|_**Description**_|
|:--------------|:----------------|
|Delay|Select whether this script should take the shot immediately or wait for 2 seconds.|
|Time|The length (in minutes:seconds) of the exposure; values range from 00:00:01 to 05:00:00.|

Notice that the camera has to be in M + BULB mode to take a long exposure; this script will set the camera for you, but configuring a suitable aperture is the responsibility of the user.

### Long Exposure Calculator ###

The long exposure calculator is a tool created to help the photographer quickly determine the exposure time required by a particular scene. The idea behind the long exposure calculator is that you can quickly measure a scene using a high ISO and a large aperture, then lower the ISO value and reduce the aperture, but increase the exposure time accordingly.

For example, let's suppose we want to photograph a night scene; we decide to use the lowest possible sensitivity (ISO100), to avoid noise, and a relatively closed aperture (f/8), to get the depth of field we need. Using those parameters, the exposure time needed may easily overpass 30 seconds, and thus we cannot use the camera to make a reliable measurement.

But we can temporarily select a high sensitivity and large aperture (ISO1600 and f/2.8, for example), measure the scene, and determine we would need a 15-second exposure with those parameters. Then we enter the long exposure calculator, lower the ISO value to 100, and close the diaphragm to f/8; the Ev indicator will display a value if -9, meaning that with the current parameters the exposure is 9 stops below the measured value. We can now increase the exposition time until the Ev indicator goes back to 0, meaning the current parameters would result in the same exposure than we had at the beginning; in our case, that means raising the exposure time from 15 seconds to 32 minutes. Finally, just press "Apply" to configure the camera with these parameters, and launch the long exposure script.

_**Notice**_: The Ev field in this calculator cannot display values smaller than -15EV or larger than +15EV.

_**Tip**_: If you plan to use a ND filter, you can measure the scene without the ND; then enter the long exposure calculator and adjust the exposure to get an Ev result inverse to the value of the ND filter. For example, assuming we have an ND8 filter (8 steps of light reduction): if the camera measures 1/120s f/4.0 ISO1600 without the filter, then select 2' f/8.0 ISO100 to achieve a Ev of +8.

## DOF Calculator ##

The DOF Calculator can help determine the depth of field of a scene, or the range of distances that will be photographed as sharp; for more information about this concept, please visit [DOF Master](http://www.dofmaster.com/index.html).

After entering the DOF Calculator, set the focal length of your lens, the aperture you are using, and the distance from the camera to the subject. The script will then display the near and far distances of acceptable sharpness. You can now change the aperture and / or the focusing distance until the depth of field displayed matches the part of your scene that you deem as important and want to remain in-focus.

When the "Max. DOF (m)" entry displays "INF!", the hyperfocal distance has been reached, and thus everything from the near distance of acceptable focus up to the infinity will be sharp.

## Script Chaining ##

Some scripts ([Intervalometer](#Intervalometer.md), [Hand Waving](#Hand_Waving.md), and [Self-Timer](#Self_Timer.md)) have an "Action" parameter, that allows the user to select another script (from ["Extended AEB"](#Extended_AEB.md), ["Flash AEB"](#Flash_AEB.md), ["Aperture AEB"](#Aperture_AEB.md), ["ISO AEB"](#ISO_AEB.md), and ["Long exposure"](#Long_Exposure.md)) that will be used when the _parent_ scripts decides to _shoot_.

This allows for the easy chaining of scripts: for example, the [Intervalometer](#Intervalometer.md) can be used to fire a sequence of 3 shots, using the [Extended EAEB](#Extended_AEB.md) script, every 5 minutes.

## Self-Timer and Mirror Lock-Up ##

Most scripts have a "2s delay" option; when this option is active, the script will wait 2 seconds before taking the first shot; if two scripts have been chained (see [script chaining](Script_Chaining.md)) only the _parent_ script will wait. Notice that this pause is performed by `400plus`, it is not related to the "self-timer" feature from your camera (there will be no visual or audible signaling). On the other hand, you also have the option to set the "drive mode" from your camera to "self-timer"; that option will affect each shot taken by any script, and your camera's self-timer will be used.

_**Note**_: Due to technical reasons, when the self-timer is active `400plus` will also activate the MLU option for the duration of any script; if the self-timer is disabled, the MLU option will be disabled too.

## Configuring Scripts ##

There are some configuration options at the "Config. Scripts" item in the [settings page](#Settings_Page.md) at [the menu](#The_Menu.md):

|_**Item**_|_**Description**_|
|:---------|:----------------|
|Disable power-off|When active (set to "Yes"), the Auto power-off option of the camera is disabled; useful when using long delays in the intervalometer.|
|LCD display|Configure the brightness of the LCD display while a script is running; saves battery, and reduces glare during night shots.|
|Indicator|Configure the blinking frequency of the blue LED while a script is running.|


---


# The Custom Modes #

## Introduction to Custom Modes ##

A custom mode is a complete snapshot containing all of the camera settings and configuration parameters. Custom modes can be used to pre-configure the camera for a specific shooting situation (like "landscape", "portrait", "low-light", "birds-in-flight", etc.), and allow you to have quick access to these configurations while shooting. Custom modes are stored on the CF card itself, and up to 16 different custom modes can be stored in each card. The number of custom modes however is unlimited, due to the fact you may use multiple CF cards each containing up to 16 of them.

### Some Notes On Custom Modes ###

Every time you move the main dial to a _scene mode_ where a _custom mode_ has been attached, and every time your camera powers on, while the main dial is set into a _scene mode_ where a _custom mode_ has been attached, `400plus` must wait for the camera to initialize the _scene mode_ and then apply the attached _custom mode_. This process requires some time, hundredths of a second in fact, but under certain circumstances your camera could take a shot before the _custom mode_ has been completely applied, thus resulting in a shot being taken using the _scene mode_ underneath.

For this reason, it is advised to wait for a second after moving the main dial to a _scene mode_ where a _custom mode_ has been attached, before taking a shot. Likewise, when waking up the camera from the auto power off state, do not keep the shutter button pressed down until a shot has been taken; press and release the shutter button instead, then press it again when the camera is fully awake, to take the first shot.

## Creating Custom Modes ##

To create a custom mode, first set your camera into one of the _creative modes_ (`P`, `Tv`, `Av`, `M`, or `A-DEP`) and configure it to your liking; now enter the [custom modes page](#Custom_Modes_Page.md) in [the menu](#The_Menu.md), select one of the custom modes, and just press `SET` (or enter the sub-menu, and then select "Save" there). Repeat as many times as needed, and save up to 16 custom modes.

## Using Custom Modes ##

To create a new custom mode, set your camera to one of the _scene modes_ ("AUTO", "Portrait", "Landscape", "Macro", "Sports", "Night", or "No flash") that you want to use as a _custom mode_; now enter the [custom modes page](#Custom_Modes_Page.md) in [the menu](#The_Menu.md), select one of the previously saved custom modes, and just press `SET` (or enter the sub-menu, and then select "Assign" there). Your _scene mode_ is now acting as a _custom mode_. Notice that you can assign any _custom mode_ to any _scene mode_, so up to 7 custom modes (from the 16 available) can be assigned at the same time.

## Changing Custom Modes ##

Once a mode has been assigned, you can easily update it: just set the camera to the _scene mode_ where that _custom mode_ is assigned, then change any parameter in your camera; now enter the [custom modes page](#Custom_Modes_Page.md) in [the menu](#The_Menu.md), select the current active _custom mode_ (it will be marked with an asterisk '`*`'), and just press `SET` (or enter the sub-menu, and then select "Update").

## Reverting Scene Modes ##

To revert a _scene mode_ back to its original behavior, set the camera to that _scene mode_ (the assigned _custom mode_ will automatically be recalled), enter the [custom modes page](#Custom_Modes_Page.md) in [the menu](#The_Menu.md), select the current active _custom mode_ (it will be marked with an asterisk '`*`'), and select "Unassign" in the corresponding sub-menu).

Notice that this action does not delete or change the _custom mode_ at all, it just unassigns it from the current _scene mode_.

## Renaming Custom Modes ##

From the [custom modes page](#Custom_Modes_Page.md) in [the menu](#The_Menu.md) you can rename any of the _custom modes_ using the following procedure:

  * Select the "Rename" option in the sub-menu for any custom mode.
  * Use `UP` / `DOWN` / `LEFT` / `RIGHT` buttons to select a character.
  * Use the `MENU` button to toggle between lowercase characters + numbers and uppercase characters + symbols.
  * Use the `JUMP` button to change the case of the selected value on the name (bottom line).
  * Use the `SET` button to copy the selected character to the name, and advance the cursor to the next position.
  * Use the front (main) dial or the `ZOOM IN` / `ZOOM OUT` buttons to move the cursor within the name (bottom line).
  * Press the `AV` button to save your changes and return to the previous menu.

Notice that there is always a character displayed on the left of each custom mode. This feature may come handy when you want to copy custom modes to and from multiple CF cards, and need to know the file-name for each of your custom modes: the character on the left of a custom mode matches the last character n the name of the corresponding file created in the CF card.

## Configuring Custom Modes ##

When a custom mode is assigned to a scene mode, you will normally expect `400plus` to load most parameters from the custom mode, but not all of them. For example, it is quite unlikely that you will want to have the menus ordered differently for each custom mode; you will probably want to be able to retain the order of the menus across custom modes.

This sub-menu of the [settings page](#Settings_Page.md) at [the menu](#The_Menu.md), you can select which parameters will be loaded from a custom mode when it is assigned to a scene mode:

|_**Item**_|_**Description**_|
|:---------|:----------------|
|Camera|Camera's shooting parameters: shutter speed, aperture, ISO, ...|
|400plus|`400plus`' own settings: language, scripts, buttons, ...|
|Menu order|Order of all items within menus.|
|Settings|Some rarely changed settings: language, video system, ...|
|Image|Image related settings: RAW/JPEG, quality, ...|
|Custom Fn|Custom function (C.Fn) settings: mirror lock-up, long-exposure noise-reduction...|


---


# Configuration #

The [settings page](#Settings_Page.md) at [the menu](#The_Menu.md) offers some advanced setting to configure both your camera and `400plus`.

## Internationalization ##

Currently `400plus` supports several languages:

  * English
  * Finnish
  * French
  * German
  * Hungarian
  * Italian
  * Polish
  * Russian
  * Simplified Chinese
  * Spanish

You can select an specific language for the menus, using the "Language" item in the [settings page](#Settings_Page.md) at [the menu](#The_Menu.md), or just leave it as "Camera" to use the same language configured at the camera menus.

Our desire is to have `400plus` be supported in as many languages as possible! If you are interested in assisting in the translation of `400plus` to a different language, we would certainly welcome your efforts. Let us know by making a request via the forum!

## Persisting AEB ##

When this option is active (set to "Yes"), the AEB settings will not be lost when the camera is powered off.

## Restore Configuration ##

This sub-menu allows to restore some configuration parameters back to their default values.

|_**Item**_|_**Description**_|
|:---------|:----------------|
|Restore settings|Restore all settings (but custom modes) back to default values|
|Restore custom modes|Restore all settings related to custom modes back to default values (_notice that this option does not delete custom modes themselves_)|
|Delete custom modes|Actually delete all custom modes.|

_**Note**_: There is no confirmation dialog for the actions in this sub-menu; once you press the `SET` button, your configuration will be gone.

## Configuring Buttons ##

Some unused buttons can be configured here to extend the camera's behavior:

|_**Item**_|_**Description**_|
|:---------|:----------------|
|Use D-Pad|When active (set to "Yes"), the buttons on the cursor pad will change their function while the user is looking through the viewfinder; see [ISO In Viewfinder](#ISO_In_Viewfinder.md) and [AutoISO In M Mode](#AutoISO_In_M_Mode.md) for more info.|
|Better DISP button|When active (set to "Yes"), the `DISP` button will change the display brightness in small increments, instead of just switch it on/off.|
|JUMP|Assign an action to the `JUMP` button while in the main dialog.|
|TRASH|Same as the JUMP button.|

The following actions can be assigned to the `JUMP` and `TRASH` buttons:

|_**Value**_|_**Description**_|
|:----------|:----------------|
|Intermediate ISO|Bump ISO by 1/8 EV (see [Extended ISOs](#Extended_ISOs.md)).|
|Repeat last script|Repeat last script executed.|
|Mirror lock-up|Toggle the MLU option on / off.|
|AEB|Press once to toggle AEB on / off; press repeatedly to roll the AEB separation from 0EV to 6EV, and then back to 0EV (off).|
|Flash on/off|Toggle the flash on and off (even if it has been raised).|

## Configuring Menus ##

Even how the menus work can be configured in `400plus`:

|_**Item**_|_**Description**_|
|:---------|:----------------|
|Warp menus|Long menus will warp around when the user moves the cursor past the last element (notice that by design, the main menu always warps, regardless of this option).|
|Navigate to main|You can navigate to the main page in the menu (see [Navigating the menu](#Navigating_The_Menu.md)).|
|Enter to main|`400plus` will directly enter the main page in the menu, instead of going to the last visited page.|
|Autosave|`400plus` will save the current page each time you exit the menu, and go back directly to that page when you enter the menu again, even if you shut down your camera.|

## Configuring Pages ##

Use the "Config. Pages" item in the [settings page](#Settings_Page.md) at [the menu](#The_Menu.md) to configure order how the pages must be displayed. Simply enter the sub-menu, and reorder the items there: the pages at the main menu follow the same other than the items in this sub-menu.


---


|<font color='red'><b><i>Attention</i></b>: Please, use the comments section below exclusively for comments about this page: typos, clarifications, suggestions...; open an issue to request support or suggest a new feature, and visit the forum for general discussions about the project.</font>|
|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|