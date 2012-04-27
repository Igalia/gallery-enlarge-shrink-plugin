Gallery Enlarge/Shrink Plugin
=============================

What is it?
-----------

*Gallery Enlarge/Shrink Plugin* is a filter for the Gallery application of the N9
(and N950) MeeGo devices which applies to a picture an enlarge or shrink effect,
also know as punch or pinch effects respectively.

Applying the filter to a picture:
---------------------------------
 * From the application grid, open Gallery
 * Pick a picture with a size equal or smaller than 512x512px (see Known Issues below)
 * Tap on the object menu and select *Edit*
 * Tap on *Enlarge - Shrink*
 * Choose the effect to be applied: Enlarge or Shrink
 * Select the radius of the effect in the radius slider
 * Tap on the screen to center the effect around the given point

Known Issues:
-------------
 * Only *PR >= 1.2* is currently supported.
 * You will need to reboot to make the icon for the plugin appear properly
 * Due to limitations in the current implementation of the filter, operating on
   images larger than 512x512 is not allowed.

In depth:
---------
Gallery is using [MeeGo Image Editor] [1] to apply filters on images. Since it uses
a plugin mechanism, it is possible to write new filters and have them appearing
into the built-in Gallery.

MeeGo Image Editor uses tiling to operate on small portions of an image and
avoid having to load it all into memory. While this approach works pretty well
for many filters, it fails for those requiring context to be applied, as it is the
case of this filter.

[1]: https://maemo.gitorious.org/meego-image-editor/ "MeeGo Image Editor"