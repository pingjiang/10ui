# Oct 15, 2007 #
### TenMilManUI ###
  * **Fixed Line and Rectangle Display**
    * [Issue 1](http://code.google.com/p/10ui/issues/detail?id=1)
    * Corrected misuse of glEnable/Disable(GL\_Texture\_2D)
    * **Affected Classes::Methods**
      * TenMilManUI::initOpenGL()
      * FontFamilyData::render()
      * Rasterable::preDraw()
      * Rasterable::postDraw()

# Oct 7, 2007 #
### TenMilManUI ###
  * **Merged Namespaces**
    * Everything is now under the `TenUI` namespace

  * **Created application simplifying macro**
    * `IMPLEMENT_TENUI_APP( _tenuiApp_ )`
    * This macro writes out the programs entry point (main function)
      * Instantiates TenUIApp
      * Instantiates `TenMilManUI`
      * calls `TenMilManUI::run()`

  * **Cleanup**
    * Removed Globals.h
    * Moved SDL\_util.h to Util folder

  * **Created conveniency global function**
    * `getTenUI()` returns the `TenMilManUI` instance

  * **Anti-aliased Lines**
    * added `glEnable(GL_LINE_SMOOTH)` to `initOpenGL()`

### TMMUI\_TestApp ###
  * Using `IMPLEMENT_TENUI_APP` macro
  * Using new TenUI namespace
  * Cleaned up code


# Oct 6, 2007 #
### TenMilManUI ###
  * **Changed** `FontManager_FT2`
    * Singleton
    * Initialized with a fonts directory
      * Loads all fonts in directory at specified pixel height.
      * Pixel height should be big enough to be scaled down for all uses
    * Reads in font files into FontFamilyData

  * **Created** `FontFamilyData`
    * Revamped version of `FontData`
    * Now is structured more intuitively around Font Families
      * Font Families have fonts for bold, italic, and bold&italic
    * More Textures (bold, italic, and bold&italic)
    * Handles it's own rendering
    * Handles scaling to different font sizes

  * **New Support Systems**
    * New TenMilManUI/Util folder
    * `class FileUtils`
      * static methods for traversing and manipulating files/folders
      * currently only has a method to return a list of files in a folder

  * **Changed** `TenMilManUI`
    * New initialization methods
      * `void initSDL`
        * broke out from init method
      * `void initOpenGL()`
        * broke out from init method
      * `void initFontManager()`
        * Calls the `FontManager_FT2::CreateInstance(fontdir, 32)`
        * Supplies method the font directory specified by `ITenMilManUIApp`
        * REQUIRES SDL/OPENGL TO BE SETUP ALREADY
          * Creates OpenGL textures for fonts

  * **Changed** `ITenMilManUIApp`
    * New pure virtual method
      * `string getFontDirectory()`
        * Supplies directory of fonts used by application

### TMMUI\_TestApp ###
  * **Changed** `TMMUI_TestApp`
    * Implemented new getFontDirectory
    * **Changed** Text Test
      * Changed colors of Text Test
      * Tests for minor issue with edges of glyphs not blending correctly
        * Dirty black outline


# Oct 5, 2007 #
### TenMilManUI ###
  * **New Graphics**
    * Shape (Abstract)
    * Rectangle
    * Line
    * Rasterable
    * Text

  * **New Support Systems**
    * FontManager\_FT2
      * Uses FreeType2
      * Handles reading in font and creating opengl texture
    * Graphics/Util Folder
    * ColorHex
      * Web color hex strings (#FFF)

  * **Breaking API Changes**
    * DisplayObject
      * preDraw/postDraw


### TMMUI\_TestApp ###
  * **New Features**
    * Implemented new TenMilManUIApp API
    * New Tests
      * Rectangle
      * Line
      * Text
      * Rasterable

  * **New Support Systems**
    * TestResources Folder
    * RasterTest
      * Images
    * TextText
      * Fonts