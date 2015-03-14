_**20130414-05**_
  * Added Icelandic translation (thanks Björn Guðmundsson).

_**20130414-04**_
  * Disable all display overlay (temporary fix for locking issues).

_**20130414-03**_
  * Hopefully fixed camera lock-ups.
  * Updated Russian translation (thanks to Drpr0).

_**20130414-02**_
  * Fixed some texts in the menus.

_**20130414-01**_
  * Fixed a bug in the AEB scripts, where an even number of shots was set, and scripts would run endlessly.

_**20130414-00**_
  * General enhancements:
    * Faster initialization.
    * Added a method to disable 400plus during boot-up.
    * Added some info to the main display.
    * Relax Av limits when a manual lens is attached to the camera.
    * New menu entry to restore settings to its default values.
  * "Presets" have been renamed to "custom modes":
    * All "scene modes" can now be configured into a "custom mode".
    * Up to sixteen "custom modes" can be saved.
    * The A-DEP mode is no longer special.
  * Scripts:
    * New "bulb ramping" script.
    * New "exposure bracketing" script.
    * Improved the long-exposure script and calculator.
    * When available, use lens' focal length for the DOF calculator.
    * Scripts now honor camera's MLU and self-timer options honored.
    * Added an option to switch the review off during a script.
  * Misc functions:
    * Multi-spot metering.
    * Fixed exposure for M mode.
    * Quick auto-exposure for M mode.
    * Named custom temperatures.
    * Use the burst count to display ISO in the viewfinder while in P and Av modes.
  * AutoISO:
    * New AutoISO algorithm for Tv mode: "Av max" is now relative to max aperture supported by the lens.
    * New AutoISO algorithm for M mode: use only real ISOs, and respect min / max limits.
    * Configurable sensitivity for AutoISO in M mode.
    * Added an option to make AEB persistent.
    * Added an option to revert D-Pad to its original function.
    * Configurable intermediate ISO step.
  * Usability enhancements to menus:
    * Added an option to disable warp menus.
    * Added an option to make main menu navigable.
    * Added an option to enter directly to the main menu.
    * Enter menu to last active page after a powercycle
    * Use ZOOM IN / OUT as PAGE UP / DOWN buttons.
  * Shortcut buttons:
    * Enhanced quick-AEB action.
    * New action: toggle flash.

_**20120415-17**_
  * Fixed Polish translation.

_**20120415-16**_
  * Added Hungarian translation (thanks Novák István).

_**20120415-15**_
  * Faster and more stable scripts.

_**20120415-14**_
  * Fixed a bug in AutoISO with manual mode.

_**20120415-13**_
  * Fixed a bug in AutoISO with large shutter values.

_**20120415-12**_
  * Updated Russian translation (thanks to "丫ｎｓ").

_**20120415-11**_
  * Longer pauses between shots: makes scripts run slower, but more stable.

_**20120415-10**_
  * Added Galician translation (Rubén Castiñeiras Lorenzo).

_**20120415-9**_
  * Updated German translation (Malte Perenz).
  * Improved display of long menus.

_**20120415-8**_
  * Added Dutch translation (Alfred Vink).
  * More stability fixes for scripts.

_**20120415-7**_
  * All scripts should be more stable now.
  * Fixed a bug that made Av change during EAEB scripts.

_**20120415-6**_
  * Fixed a bug that broke all AEB scripts when launched from the intervalometer.

_**20120415-5**_
  * Updated the Spanish translation (thanks JmTD!).

_**20120415-4**_
  * Fixed a bug (options not being saved when leaving the menu) introduced in 20120415-3.

_**20120415-3**_
  * Fixed a typo.
  * Fixed a bug when closing the menu.
  * Fixed the AF dialog when pressing DISP.

_**20120415-2**_
  * Fixed a bug in the page navigation.

_**20120415-1**_
  * Updated Russian translation.
  * Fixed a bug in the page reordering submenu.

_**20120415-0**_
  * Usability improvements
    * New language system: now 400plus can be translated to languages not supported by the camera.
    * Menus have been reordered, everything should be easier to find now.
    * JUMP and TRASH buttons are now configurable (on the main dialog).
    * DISP button can be used to change brightness in small increments.
    * Use UP to display current ISO in the viewfinder (without changing it).
  * New scripts
    * Long exposure script, with long exposure calculator included.
    * Depth-of-field and hyperfocal calculator.
    * ISO and Flash AEB.
  * Enhancements to scripts
    * Strict scheduling and time-lapse calculator added to the intervalometer.
    * Bracketing direction configurable for EAEB.
    * LCD brightness and blinking LED during scripts are now configurable.
    * Restore camera before shut down, and check for card space before each shot.
  * New and updated translations
    * Finnish.
    * Russian.
    * Polish.
    * The translation procedure has also been made easier.

_**20111111-4**_
  * Fix a rare occurrence of an out-of-limis value.

_**20111111-3**_
  * Removed some debugging code.

_**20111111-2**_
  * Fixed EAEB for long (>30") exposures.

_**20111111-1**_
  * Minor bugfixes only.

_**20111111-0**_
  * New multi-page menus.
  * Improved reliability of scripts.

_**20110904-1**_
  * Updated Spanish translation (thanks JmTD at Canonistas).

_**20110904-0**_
  * AutoISO
  * Intermediate ISOs reworked: 1/8 EV resolution, false ISO-3200 removed.
  * Translations saved in a separate INI file.
  * All three possible file formats (JPEG, RAW, RAW+JPEG) available in AUTO modes.
  * New shortcut: color temperature.
  * Rolling menus.
  * Debug on power-on and log file mode selection.

_**20110615-4**_
  * French translation added.
  * Italian translation updated.

_**20110615-3**_
  * Italian translation added.

_**20110615-2**_
  * Spanish translation added.

_**20110615-1**_
  * Bugfixes only.

_**20110615-0**_
  * Lots of improvements regarding usability at the menus; several buttons have been reassigned, please see the [UserGuide](UserGuide.md).
  * SET is no longer needed to apply settings or save changes in any menu.
  * The number of available presets has been increased to 9.
  * Latest preset "used" (loaded or saved) is highlighted in the presets' menus.
  * The presets' menus can now display file-names instead of user-defined names (useful to identify which file contains what preset).
  * When moving the main dial out of A-DEP and back, the last preset used is recalled completely (not just the AE mode).
  * White balance is automatically changed to "custom" when color temperature is changed.

_**20110517-0**_
  * Multi-language support (only English and German right now).
  * Presets have been improved, there are more options related to them, and now they can be renamed and reordered.
  * Some enhancements for the scripts:
    * Disable MLU and auto power-off during the execution of a script.
    * Dim LCD down during the execution of a script.
    * EAEB exposures up to 16 minutes.
  * Other minor additions and fixes.

_**20110425-1**_
  * Fixed wrong version number displayed.

_**20110425-0**_
  * New "Presets" feature.
  * More info (BodyID) at the INFO dialog.
  * AF settings moved to the shortcuts dialog and expanded.

_**20110412-0**_
  * The shortcuts menu acts now like a real menu, only that it can be reordered.
  * Optionally, the shortcuts menu can be disabled, and then the DP button will change to an intermediate ISO.
  * Sub-menus at the settings menu are now navigated using the front wheel.
  * Displayed release count and 400plus version at the INFO menu.
  * Added new developers menu to enter / leave the factory mode or activate the debug mode (use with care, or even better, do not use at all).
  * And lots of other minor improvements and bug fixes.

_**20110403-0**_
  * Added the configuration of the shortcuts menu.
  * Added a couple of new shortcuts.

_**20110328-0**_
  * Added the shortcuts menu.

_**20110323-0**_
  * Added an option to run the Wave script endlessly.

_**20110318-2**_
  * Fixed another bug (flash-related options act inverted).

_**20110318-1**_
  * Fixed a bug (highlighted line does not match active line when returning to menu).

_**20110318-0**_
  * New menu infrastructure.

_**20110314-0**_
  * Code clean-up.

_**20110211-0**_
  * Deactivate UP / DOWN buttons when camera is at the face, to avoid changing ISO / WB with your nose.
  * Better detection of double-event buttons, and some code clean-up.