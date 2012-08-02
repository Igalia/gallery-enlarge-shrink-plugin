Gallery Enlarge/Shrink Plugin
=============================

What is it?
-----------

*Gallery Enlarge/Shrink Plugin* is a filter for the Gallery
application of the N9 (and N950) MeeGo devices which applies a radial
distortion to a picture.

From the [Wikipedia] [1],
> ### Barrel distortion
> 
> In *barrel distortion*, image magnification decreases with distance
> from the optical axis. The apparent effect is that of an image which
> has been mapped around a sphere (or barrel). Fisheye lenses, which
> take hemispherical views, utilize this type of distortion as a way to
> map an infinitely wide object plane into a finite image area.
> 
> ### Pincushion distortion
> 
> In *pincushion distortion*, image magnification increases with the
> distance from the optical axis. The visible effect is that lines that
> do not go through the centre of the image are bowed inwards, towards
> the centre of the image, like a pincushion. A certain amount of
> pincushion distortion is often found with visual optical instruments,
> e.g., binoculars, where it serves to eliminate the globe effect.

These distortions provide enlarge or shrink effects, also know as
punch or pinch respectively.

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
Gallery is using [MeeGo Image Editor] [2] to apply filters on images. Since it uses
a plugin mechanism, it is possible to write new filters and have them appearing
into the built-in Gallery.

MeeGo Image Editor uses tiling to operate on small portions of an image and
avoid having to load it all into memory. While this approach works pretty well
for many filters, it fails for those requiring context to be applied, as it is the
case of this filter.

[1]: https://en.wikipedia.org/wiki/Distortion_%28optics%29#Radial_distortion "Radial Distortion"
[2]: https://maemo.gitorious.org/meego-image-editor/ "MeeGo Image Editor"
