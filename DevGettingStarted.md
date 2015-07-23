# Introduction #

This guide will take a developer through the steps to building TenUI.

# Prerequisites #
  * Linux Kernel 2.6+
  * GNU GCC 4.2+
    * TenUI makes use of some TR1 C++ libraries
  * SDL
  * FreeType

# Step 1: Development Tools #
## Eclipse ##
http://www.eclipse.org/downloads/moreinfo/c.php

## Subclipse SVN/Eclipse Plugin ##
http://subclipse.tigris.org
  * Use the Eclipse Update Site http://subclipse.tigris.org/update_1.2.x

# Step 2: Checking out TenUI/TenUI\_TestApp #
  * SVN logon and path information: http://code.google.com/p/10ui/source

![http://10ui.googlecode.com/svn/wiki/resources/DevGettingStarted_files/Eclipse_SVN_Perspective.png](http://10ui.googlecode.com/svn/wiki/resources/DevGettingStarted_files/Eclipse_SVN_Perspective.png)

![http://10ui.googlecode.com/svn/wiki/resources/DevGettingStarted_files/Eclipse_SVN_Checkout.png](http://10ui.googlecode.com/svn/wiki/resources/DevGettingStarted_files/Eclipse_SVN_Checkout.png)

# Step 3: Building the TenUI Library #
Make sure you are in the C/C++ Perspective and the C/C++ Projects View is visible
![http://10ui.googlecode.com/svn/wiki/resources/DevGettingStarted_files/Eclipse_C_Cpp_ProjectsView.png](http://10ui.googlecode.com/svn/wiki/resources/DevGettingStarted_files/Eclipse_C_Cpp_ProjectsView.png)
![http://10ui.googlecode.com/svn/wiki/resources/DevGettingStarted_files/Eclipse_BuildProject.png](http://10ui.googlecode.com/svn/wiki/resources/DevGettingStarted_files/Eclipse_BuildProject.png)

A successful build will result to the a console looking like the following:

![http://10ui.googlecode.com/svn/wiki/resources/DevGettingStarted_files/Eclipse_FinishedBuilding.png](http://10ui.googlecode.com/svn/wiki/resources/DevGettingStarted_files/Eclipse_FinishedBuilding.png)

## Possible Compile/Linker Errors ##
Your particular setup may have the includes and libraries for SDL, FreeType, and OpenGL in a different location then is expected in the default build configuration.  Make sure that the directories for includes and libraries for SDL, FreeType, and OpenGL are correct by looking in the CDT Build Settings.
![http://10ui.googlecode.com/svn/wiki/resources/DevGettingStarted_files/Eclipse_CDT_Include.png](http://10ui.googlecode.com/svn/wiki/resources/DevGettingStarted_files/Eclipse_CDT_Include.png)
![http://10ui.googlecode.com/svn/wiki/resources/DevGettingStarted_files/Eclipse_CDT_Libraries.png](http://10ui.googlecode.com/svn/wiki/resources/DevGettingStarted_files/Eclipse_CDT_Libraries.png)