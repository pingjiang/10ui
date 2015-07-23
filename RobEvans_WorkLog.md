## Work log ##
### Thurs 12/6/07 ###
  * Get latest code from svn (fixed event system)
  * Modified !SDLMouseInput to generate PointEvent InputEvents
  * Registered InputManager with !SDLMouseInput to receive events
### Wed 12/5/07 ###
  * Tracking down problems with new event system
    * Found the problem was in InputManager::handleInputEvent
      * Trying to access any info from the event appears to crash it
      * Trying to output a simple string in the function (not a member of the event)
    * Peter was able to debug it and find the problem
      * !SDLMouseInput wasn't declaring what events it'd be throwing which caused it to die
      * Though the mistake could have been avoided on my part, in debugging Peter found a different error
### Mon 12/3/07 ###
  * Something's wrong - TMMUI TestApp immediately terminates on startup, despite debug outputs no output is output
    * Last change before error, implementing new event system
      * Tried commenting out new material w/o success
### Sat 12/1/07 ###
  * New event system
    * %Y% UserInputEvent, PointEvent created
    * %Y% InputManager -> EventDispatcher and EventHandler
  * Remove intermediate BasicInput or MultiInput
    * From...
      * !SDLMouseInput - DONE
      * TableInput\_NewArch - DONE
  * !TenUI app function registerInput(new UserInput) will call InputManager::registerInput(UserInput ui) to register itself
    * Move initialization code for UserInputs from init() to constructor - DONE
    * Remove self-registration to InputManager, will be done through the app - DONE
  * TODO:
    * UserInputs will dispatch UserInputEvents which InputManager will handle
### Wed 11/28/07 ###
  * Helped Ted w/ debugging
    * Found cvHALd wasn't running
    * Got TestDeviceApp running for Ted so he could test his zoom listener
  * Having issues with my own code
    * Working from pitfall
    * Libraries "not found" but required by libOverhead\_Events.so, warning reported in TMMUI`_`TestApp
      * libcv.so.1
      * libcvaux.so.1
      * libcxcore.so.1
      * libhighgui.so.1
    * All "missing" libraries are in Table\_Libs\_Includes/lib/opencv
    * Commented out Draggable and Selectable controls, they were trying to register with {Select,Drag}Managers
  * Meeting
    * Set timetable - drag,zoom,rotate by Dec.7th
  * Worked with Thomas to resolve issues
    * %Y% First issue, individual events for each finger - SOLVED, error in my debugging code
    * %N% Second issue, only one hand's events registered - UNRESOLVED
    * %N% New issue, nan being given for points - UNRESOLVED
  * TODO:
    * Coordinate stuff - on hold
### Mon 11/26/07 ###
  * Peter
    * Talked to him
      * ...about State machine design
        * Test case - Dragging Sandtable units
      * ...about implementation
        * Move event handling from controls to state machine
        * Move event creation from {Select,Drag}Managers to InputManager
    * Emailed him regarding 10ui coordinate stuff
      * 10ui window coordinates
      * Determining user's screen resolution
      * Multiple 10ui windows in future?
  * Emailed Thomas regarding odd behavior w/ new architecture
    * Only one hand generating events
    * Every point generating a TouchRawEvent
  * Removed {Select,Drag}Manager execution from 10ui test app
### Mon 11/19/07 ###
  * "Playing" with new architecture on TestDeviceApp
    * PROBLEM: Multiple hands cause issues
      * All points are registered (ids are assigned 0-7 for example) just fine [good ](.md)
      * %N% Only points associated with the first hand (whichever side that may be) are sent as events [bad ](.md)
      * Unpresses (as in the old architecture) are always registered [good ](.md)
      * [Debugging log](http://www.vrac.iastate.edu/~robevans/new_arch_debugging.txt)
    * Better tracking with polarized light may fix, but thumbs aren't usually registered (cross is in front of hand -> so thumb is too far away)
    * Small issue: Points' sides don't change when a arm changes sides%BR%
> > > ![http://www.vrac.iastate.edu/~robevans/Side_switching.png](http://www.vrac.iastate.edu/~robevans/Side_switching.png)
  * Interpreting data from TableInput\_NewArch
    * PROBLEM: When registering with InputManager, test app exits
      * Found that when I changed TableInput\_NewArch back to BasicInput (from MultiInput) it works
      * TEMPFIX: Make TableInput\_NewArch a BasicInput again
      * The problem appears to be that {Select,Drag}Managers use a dynamic cast to a BasicInput to get the data
      * FIX: Add cases for MultiInput to {Select,Drag}Managers
    * Modified debug output for easier analysis (uniform formatting, easier to understand the data)
    * PROBLEM: The edge point doesn't seem to be getting sent (may just not be implemented yet)
    * Removed debug output from TouchRawEvent::decode() and recompiled the library
    * IMPORTANT NOTE: When run in fullscreen-mode, table coordinates coincide w/ non-fullscreen resolution
      * Ex. 1280x1024 (normal res), running test app 640x480 (fullscreen) -> coordinates from table are in 1280x1024
    * Something seems amiss with the TouchRawEvents, instead of processing multiple fingers per event, it seems to just be sending one event per finger.
### Tues 11/13/07 ###
  * Updating new architecture files
    * Updated my workspace to include the latest DeviceCore, Touch\_InputDevice and Overhead\_InputDevice files
    * Had an issue with some files that had conflicts, my changes were minor so I just reverted
  * Troubleshooting with Thomas
    * Found some problems with the new architecture programs
      * Seg faults when nooverhead is used (used to seg fault when overhead was used)
      * Having issues tracking the first hand it goes to the same point off the screen (1015,-96 or something)
        * This explains touch problems with one hand
      * Tracking seems to work successfully on other sides
    * Successfully ran Thomas's test program for the new architecture
    * Successfully ran TMMUI`_`TestApp with the new architecture input
      * Only reading raw data and none is actually used, but it's a step forward
  * TODO:
    * Translate coordinates for the TableInput; screen(absolute) ==> window(absolute)
    * Interpret TableInput, should behave similarly to mice
    * PROBLEM: Current programming supports hovering over a single object (multiple hands not taken into account)
### Mon 11/12/07 ###
  * PROBLEM: Can't log in to shirley or pitfall
  * Moved to an AMD64 machine
    * Switched over all the libraries to their 64-bit equivalents
    * Found that there wasn't a 64-bit library for cvHAL
  * Moved to a 32-bit machine
    * Switched back to the 32-bit libraries
  * FIX: To the problem of {Select,Drag}Manager independence
    * Put last\_ui in InputManager and let it keep track of last inputs (a single last\_ui per input)
    * PROBLEM: Different types of input
  * UserInput
    * Moving common elements further up
      * quit, isQuit() -> UserInput
      * x, y, pressed, getX(), getY(), isPressed() -> BasicInput
      * x[.md](.md), y[.md](.md), pressed[.md](.md), getX(index), getY(index), isPressed(index) -> MultiInput
    * Tried switching TableInput\_NewArch from BasicInput to MultiInput, but it keeps complaining
      * FIX: TableInput\_NewArch was created hastily and was just a copy of MultiInput, so the #ifndef was still MULTIINPUT\_H`_` instead of TABLEINPUT\_NEWARCH\_H`_`
### Fri 11/9/07 ###
  * UserInput
    * Removed debugging stuff {UI\_type, UI\_data}
  * TableInput\_NewArch
    * Changed to a subclass of BasicInput (essentially the same as UserInput right now)
  * BasicInput
    * Moved getX(), getY(), isPressed() from UserInput to BasicInput
    * Now uses dynamic\_cast in SelectMgr::_update and DragMgr::_update to get data (since getX(),getY() etc. isn't in UserInput)
  * UIComponent
    * Removed all permission related stuff
    * Removed all state data
  * {Select,Drag}Manager
    * Removed all state change info
  * Subclass UIComponent with SelectableComponent
    * Since SelectManager and DragManager will be running independently it doesn't make sense to register with both
  * Demo
  * {Selectable,Draggable}Components
    * Constructed from UIComponent and DraggableComponent with Peter's conception of dragging in mind
    * DraggableComponents will not be selectable
    * SelectableComponents will not be draggable
    * DraggableComponents may have children that are selectable
    * SelectableComponents may have children that are draggable
  * DragManager
    * enabled[uid](uid.md) = true (in init()), because SelectManager and DragManager are now independent
    * adding code for sending DRAG\_COMPLETEs
  * DragSource
    * Possibilities
      * union like SDL\_Event
      * template class like STL stuff
      * void data which is casted based on dragDataFormat
    * Implemented basics
    * Implemented getDragData() and receiveDragData(data) for DraggableRectangle
      * Now allows for dragging of text data from one ctrl to another (overwriting it)
      * Tried both copying and moving data
  * Children (or any overlapping ctrls of differing type (Selectable vs Draggable)
    * Tried messing with a Selectable parent with a Draggable child
    * PROBLEM: With {Select,Drag}Managers completely independent, they do their hovering and clicking simultaneously
### Thurs 11/8/07 ###
  * 10ui and the table
    * Got 10ui compiling with the new table architecture plugged in (basically Peter adding necessary libraries until it worked)
    * Didn't know which host and ports to connect to - talking to Thomas for that
  * Talked with Peter about new classes for 10ui
    * State Manager
    * States
### Wed 11/7/07 ###
  * {Select,Drag}Manager
    * Debugging issue with dragging
      * Theory: The reason it only works the first time is b/c SelectMgr and DrgMgr aren't sharing allHoveredObjects[uid](uid.md) and last\_ui[uid](uid.md)
      * %N% FIX: Moving that data to a shared location
        * To UserInput:
          * Easy solution
          * Would it be a problem?
          * Putting last\_ui WOULD be a problem, if we subclass UserInput for "AdvancedInput" (vs BasicInput) then it wouldn't use the same Input class...
          * Trying just sharing allHoveredObjects[uid](uid.md)
        * Seems common location didn't fix the problem
        * New observation: When dragging, if a NULL area is passed over it works fine
          * (works) [obj](src.md) 

&lt;space&gt;

 [obj](target.md)
          * (doesn't work) [obj](src.md)[obj](target.md)
      * %Y% FIX: Allow SelectManager and DragManager access to each others allHoveredObjects
        * Works, but should be implemented w/o making the data public
    * Corrected behavior for "unused" events (ex. DRAG\_DROP on empty space)
  * Experimenting with typedef union for Event class
    * Based off of SDL\_Event (see TenMilManUI/includes/SDL/SDL\_events.h)
    * If I understand correctly, union would allow for us to use the same Event class but have a "type" member specify what other data is present
    * SDL\_Event does this in the same way, first it differentiates between different types of events and allows further processing from there
  * Experimenting with typedef union for use with DragSource
  * Table project meeting
  * TODO:
    * State classes
      * Permissions will be moved here for state changes
    * Can a DraggableComponent be selected by the SelectManager?
      * YES - Then DraggableComponent must remain a subclass of UIComponent
      * NO - Why should DraggableComponent be a subclass of UIComponent then???
### Mon 11/5/07 ###
  * {Select,Drag}Manager
    * Convert use of UserInput as an identifier to uid as the identifier
    * Continuing work on changing ctrl states
      * Having an issue with dragging
        * Test sequence
          * (A)::HoverIn
          * (A)::Pressed
          * (A)::HoverOut [!DragMgr enabled ](.md)
          * (B)::DragEnter
          * (A)::DragComplete
          * (B)::DragDrop [!SelectMgr enabled ](.md)
          * (B)::HoverOut
          * (A)::HoverIn
          * (A)::Pressed
          * (A)::HoverOut [!DragMgr enabled ](.md)
          * (A)::DragComplete
          * (B)::DragDrop [!SelectMgr enabled ](.md)
          * (B)::HoverOut
        * Missing DRAG\_ENTER event for repeated drags
  * Event
    * Added copy constructor
### Sat 11/3/07 ###
  * %Y% DragManager
    * Modeled closely after SelectManager
    * last\_ui, allHoveredObjects
    * init(), update()
  * %Y% Restructuring all Managers to singleton design
    * Manager
      * init() -> init(), update() -> update()
    * SelectManager, DragManager
      * virtual {init() -> init(), update() -> update()}
      * static {inst, allHoveredObjects, last\_ui}
      * static {init(), update(), instance(), createInstance()}
  * %Y% Moving SelectManager, DragManager calls library-side
    * init() now called by !TenMilManUI::TenMilManUI()
    * update() now called by !TenMilManUI::run()
    * Had to move the DragManager.h, SelectManager.h includes from !TenMilManUI.h -> !TenMilManUI.cpp b/c it was having dependency issues
  * %Y% {Select,Drag}Manager
    * Added static {enable(uid), disable(uid)}
    * Seems like there may be a better way than my approach
    * For event packaging, added uid
    * Move implementation from .h -> .cpp
    * Clean update() so the order and execution is clear
  * Event
    * Added uid (already "id", but unused -> changed id=>uid)
  * UIComponent
    * Moved implementation from .h -> .cpp
    * Moved registration (with SelectManager) to UIComponent constructor
    * Added bool dragAllowed(uid) which always returns false, which is overwritten by DraggableComponent
  * DraggableComponent
    * Moved implementation from .h -> .cpp
    * Moving registration (with DragManager) to DraggableComponent constructor
  * {Select,Drag}Manager
    * Deal with ctrl state in update()
    * Deal with switching managers {Select->Drag, Drag->Select}
  * Changed EventHandler::objid to evtHandlerid
  * Started work on changing ctrl state
  * PROBLEM: Need to share last\_ui between {Select,Drag}?
  * Removed changes to SelectManager::update() and DragManager::update()
    * Noticed problems in behavior
    * FIXED Tracked it to a change in update() where a pointer had been assigned before, but now it was just using the values (so the values didn't get saved back to last\_ui)
  * Managers need to share last\_ui from inputs
    * Attempted to put in BasicInput, can't get data from its subclasses
    * Put in Manager class, seems like it could cause problems later on
    * In InputManager class, sets Manager::last\_ui during each update, cause skipping?
    * Need a magic input class later on, to be implemented like SDL\_Event using union
    * Reason we need to share between managers, if a drag is started then finished SelectManager get amnesia, remembering only when the drag started way back when => therefore, immediately execute {HOVER\_IN,UNPRESS,CLICK} b/c the last input is from way over there
  * TODO:
    * Update update() to change ctrl states in {Select,Drag}Manager - IN PROGRESS
    * Implement DragSource class for Xfering data, implement like SDL\_Event using union
### Fri 11/2/07 ###
  * SelectManager
    * init()
      * Added code to get a starting point from each input
      * Originally just started last\_ui with blank Input
    * Moved Input struct to Manager so both {Select,Drag}Manager can use it
  * UserInput
    * Added static nextUID
    * Added uid so UserInputs will be unique across subclasses (just like DisplayObject subclasses)
    * Added getUID()
  * !SDLMouseInput
    * Looked up the info for keeping track of entering and exiting the window
    * Added code for entering/exiting for use later, marked with a TODO
  * InteractiveRectangle
    * In the constructor commented out the registration of event handlers (so I can focus on relevant outputs)
  * DraggableComponent %N%
    * Subclass of UIComponent
    * Added DragSource getDragData()
    * Added bool receiveDragData(DragSource data)
    * Added bool dragAllowed(uid) which checks permissions
  * UIComponent
    * Added setState() to set the componentState
    * Added bool selectAllowed(uid) which checks permissions (should also check locked state?)
  * InputManager
    * Added getInput(uid) which returns a UserInput given a uid or NULL if uid doesn't exist
    * Added support for groups
      * bool isMember(uid,gid)
      * Left adding group logic itself for later, currently just returns true
      * Perhaps gid(0) could be all users and specify other groups later
  * permissions
    * Created permissions struct to handle permissions for select/drag
    * bool {all, owner, group, default}
    * unsigned long {owner\_uid, group\_gid} (no such thing as a gid yet...)
    * void setPermissions(bool,bool,bool)
  * Manager
    * have bool enabled[of !UserInputs](#.md)
### Sat 10/27/07 ###
  * !UIComponent
    * Added !UIComponent state constants {HOVERED\_STATE, PRESSED\_STATE, ~~DRAGGING\_STATE~~, IDLE\_STATE}
    * Added componentState(string) to keep track of control states
    * Added getState() to return componentState
  * InteractiveRectangle
    * Added statements to basic event handler (itself) to maintain internal state based on events
  * Planning (very long TODO)
    * Drew state diagrams for !UIComponents and DraggableComponentz, it's pretty l337 (finally used !CmpE 210 & ComSci 331 for something)
      * [[UIComponent state diagram](http://www.vrac.iastate.edu/~robevans/UIComponent_state_diagram.png)]
      * [[DraggableComponent state diagram](http://www.vrac.iastate.edu/~robevans/DraggableComponent_state_diagram.png)]
    * Will need permissions for selecting and dragging, I think a simple struct should do
      * bool all(enabled/disabled), owner, group and default
      * string or long(as id) for owner, group id
    * !UIComponent
      * New subclass DraggableComponent
      * When changing states (in control's basic(built-in) event handling) check if:
        * already locked
        * state change requires privileges
      * Move display changes from event-specific to state-specific
    * DragSource
      * void data
      * string format { TEXT, OBJECT, ? }
    * DraggableComponent, public !UIComponent
      * Additional state DRAGGING\_STATE (here instead of in !UIComponent)
      * allowedDragActions { COPY, MOVE, LINK }; LINK may be unnecessary
      * allowedDragFormats { TEXT, OBJECT, ? } == DragSource::format
      * DragSource getDragData() { packages data based on control type }
      * bool? receiveDragData(DragSource data) { handle data }
    * Need to define groups for permissions somewhere
      * Define as rules ex. { uid | uid > 2 }
      * Define as sets ex. { 0, 2 }
    * UserInput
      * Need to change UserInputs so uid is universal among different UserInput subclass
      * Currently each type of UserInput has it's own uid assignment
      * Add input states { HOVERING, DRAGGING, PRESSED } so after a control is released, if other user inputs are waiting for a control they can get attention
      * There MUST be a better way than checking all the inputs after a control is released => adding states to input is on hold 'til I figure out whether there is another way
  * Copied SelectManager files so I could make changes and revert if needed, but I didn't get around to it with all the planning :(
  * TODO:
    * SelectManager
      * Improve update() code
      * Make a singleton
      * Move call to update() from app-side to library-side
      * Modify so only top object is used (even for HOVER)
    * DragManager
    * Add timing measures for performance
      * For SelectManager::update()
      * For draw()
    * CursorManager[low priority ](.md)
### Fri 10/26/07 ###
  * UIComponent
    * Added selectEnabled property
    * Added dragEnabled property
    * Added drag constants DRAG{ENTER,MOVE,EXIT,DROP,COMPLETE} (for DragManager eventually)
  * SelectManager
    * Making update() code better
      * Modifying implementation to only HOVER one object
      * Bug: Modification caused possibility of multiple HOVER\_OUTs for same object
      * Objects should have states so actions can't transfer (ex. PRESS in one square should UNPRESS when HOVER\_OUT)
  * TODO:
    * SelectManager
      * Improve update() code
      * Make a singleton
      * Move call to update() from app-side to library-side
      * Modify so only top object is used (even for HOVER)
    * DragManager
    * UIComponent
      * ~~Add selectEnabled property~~
      * ~~Add dragEnabled property~~
    * Add timing measures for performance
      * For SelectManager::update()
      * For draw()
    * CursorManager [low priority ](.md)
### Thurs 10/25/07 ###
  * Researching drag managers
    * Flash/Flex implementation
    * Planning TenUI::DragManager
  * Discussed with Peter
    * DragManager - conflicts with SelectManager? turn each other off (for specific user(s)) while processing?
    * CursorManager - already have user id (side), use specific cursors for specific users to show differentiation - save for later
    * selectEnabled, dragEnabled properties to be added to !UIComponent to determine behavior
    * HOVER events no longer to affect all objects at a point, only top object
  * TODO:
    * Move SelectManager->update() to a better location (TestApp::update() to...?)
    * Make SelectManager a singleton with static members (modeled after Flex implementation)
    * Add timing measures for performance
      * For SelectManager::update()
      * For draw()
    * ~~Research drag manager implementation~~
    * Improve code for SelectManager
    * Start work on DragManager
### Wed 10/24/07 ###
  * Continuing investigation of multiple HOVER\_INs and HOVER\_OUTs
    * Implemented an ltoa function (opposite of atol) to display rectangle IDs
    * Found that multiple INs and OUTs were correct, simply entering three rectangles simultaneously for a split second before leaving them because there's a table event at a common point
  * Table meeting
  * Organizing tasks
  * TODO:
    * Move SelectManager->update() to a better location (TestApp::update() to...?)
    * Add timing measures for performance
      * For SelectManager::update()
      * For draw()
    * Research drag manager implementation
    * Improve code for SelectManager
### Tues 10/23/07 ###
  * Removing HOVER\_MOVE events
  * Investigating multiple HOVER\_INs and HOVER\_OUTs for single TableInput events (there should only be one HOVER\_OUT and one HOVER\_IN)
### Mon 10/22/07 ###
  * Problem: Lag, with multiple UserInputs it gets bogged down figuring out which objects are hovered/not hovered
    * Possible fix: Take out the HOVER\_MOVE event since I can't think of any possible uses
    * Review code; see if it can be optimized anywhere
  * Helped Ted with a manual for demos
    * Found rygar isn't working
    * Walked him through necessary steps for other demo apps
  * Problem: There seems to be way too many events being thrown by the test TableInput ex. it'll send out 3 hover\_in & hover\_outs at a time
    * Need to look through code (already will be to optimize for above problem)
### Fri 10/19/07 ###
  * Initial attempt
    * Inserting BasicInput
      * TableInput, SDLMouseInput now subclass BasicInput
      * Data (x,y,pressed,quit) and methods moved to BasicInput
    * Creating InputManager
      * Since UserInput and InputManager are now differentiated, UserInput subclasses can use isQuit() and update() (instead of getQuit() and run\_update())
    * %X% Compile was unsuccessful, didn't manage changes well enough - went back to previous code
  * Attempt #2
    * Creating InputManager
      * %Y% Initially in addition to UserInput
      * %Y% Change UserInput subclasses to register with InputManager additionally
      * %Y% Switch the application from using UserInput to InputManager
    * Modifying UserInput
      * %Y% Remove references to static vars from subclasses
      * %Y% Remove static vars & methods (that are now in InputManager)
      * %Y% Changing virtual functions back getQuit()->isQuit(), run\_update()->update()
      * %Y% Added {UI\_type,UI\_data,getType(),getDataFormat()} and the static vars {MOUSE\_INPUT,TABLE\_INPUT,BASIC\_DATA,GESTURE\_DATA,REALTIME\_DATA}
    * Modifying TableInput for multiple instances (one per user)
      * %Y% Removed static vars & methods {isCreated, inst, instance()} except createInstance()
      * %Y% Expanded createInstance()->createInstance(uid)
    * Inserting BasicInput
      * %Y% Subclass UserInput with BasicInput
      * %Y% Move SDLMouseInput and TableInput from under UserInput to under BasicInput
    * Fixing SelectManager for multiple inputs gracefully
      * Added init() function which fills in a map of UserInput**-> Input** for last inputs of each UserInput
      * Modified update() function to use the <UserInput,Input> map to retrieve and update the correct last\_ui
      * Added map<UserInput**,set<UIComponent**> > for hovered objects for each UserInput
        * Tried implementing really quick - seg fault (I forgot to initialize the map's stuff in init() - TODO)
  * TODO:
    * Make UserInput(/InputManager now) handle multiple inputs
      * %Y% Insert BasicInput between UserInput and {SDLMouseInput,TableInput}
      * Fix SelectManager for multiple inputs (handle things and extra data gracefully)
      * %Y% One UserInput per user for TableInput (singleton->not singleton)
      * %Y% Create InputManager to keep track of inputs (rather than in UserInput)

### Thurs 10/18/07 ###
  * Modifying UserInputs
    * Changed virtual bool UserInput::update() to static bool UserInput::update() and added virtual bool UserInput::run\_update()
    * In the subclasses 

&lt;class&gt;

::update() was changed to 

&lt;class&gt;

::run\_update()
  * Modifying SelectManager
    * Need to SelectManager::update() for each UserInput -> added a little temporary struct for handling data, "Input"
    * Added SelectManager::last\_m,last\_t which are Input (so update() doesn't confuse the last A from the last B)
  * Oy. Just realized we'll need last for EVERY user on the table since we don't want them to interfere with each other
    * Already knew we'd need to make a dynamic # of last (for different #s of inputs) but I didn't even think about multiple users
    * Mapping out exactly what we'll want to interact as far as hovering is concerned and additional data that'll be needed
      * uid // user id data attached to events
      * UserInputs are processed one at a time, mouse input shouldn't affect table input
      * Within table inputs, at least for the old architecture, ~~we won't even want different fids interacting~~ no fids, only hover on hands
  * TODO:
    * Make UserInput handle multiple inputs
      * Find out what additional info is gonna need to be stored (I'm worried it may be a lot... sets of !UIComponent pointers for each fid)
    * Insert BasicInput between UserInput and {!SDLMouseInput,TableInput}
    * Fix SelectManager for multiple inputs (handle things and extra data gracefully)
    * One UserInput per user for TableInput (singleton->not singleton)
    * Create UserInputManager to keep track of inputs (rather than in UserInput)
### Wed 10/17/07 ###
  * Removed select from !SDLMouseInput and TableInput
  * Modified SelectManager::update() to interpret "selects" (clicks)
  * Realized for HOVER\_IN, HOVER\_OUT and HOVER\_MOVE we'll want to send it to ALL objects at a point, not just the top object
    * Modifying obj -> objs in SelectManager
  * Got all the events working
    * Realized it wasn't processing them in with the proper order -> doesn't go through registeredHandlers just handles the events itself
    * FIX: create !UIComponent::processEvent(Event) which will check the registeredHandlers
  * Added Shape::setFillColor(r,g,b) and Shape::setStrokeColor(r,g,b)
  * Added Shape::getFillColor(r,g,b) and Shape::getStrokeColor(r,g,b)
  * %X% Removed userInput member of !TenMilManUI replacing it with static functions of UserInput
    * Changed UserInput::isQuit() from a pure virtual function to a static function that returns true if ANY of the UserInputs returns true isQuit() and false otherwise
    * Changed UserInput::update() from a pure virtual function to a static function that returns false if there aren't any UserInputs instantiated, otherwise it updates all UserInputs and returns true
  * Added userInput member back in after failing testing
  * TableProject Meeting
  * Attempting to allow for multiple UserInputs again...
    * Started out slow - remove userInput
    * Replace !ITenMilManUI::getUserInput() with !ITenMilManUI::initializeUserInput()
      * New function is void and simply instantiates the UserInputs w/o returning their values, implemented in !TMMUI\_TestApp.h
      * In !TenMilManUI::TenMilManUI(app) run initializeUserInput() rather than getUserInput()
    * In !TenMilManUI::run()
      * Replace userInput->{update(),isQuit()} with !SDLMouseInput::instance()->{update(),isQuit()} (since !SDLMouseInput is the only way to quit currently)
      * %X% Problem? How will TableInput be processed? If TableInput->update() pops an event off a queue of events we'll have problems; can't run TableInput->update() in !TenMilManUI::run() AND SelectManager->update()
        * Peter said SelectManager shouldn't be updating the UserInput, it should just assume !TenMilManUI::run() has updated it already
      * %X% New problem? If !TenMilManUI::run() updates UserInput from the table (popping off events from it) what if run() runs faster than SelectManager::update() lost events?
        * Possible fix: Put in a queue somewhere for TableInput::update() to shove events onto so SelectManager can handle them in it's own sweet time
    * %Y% So far so good...
      * Changed virtual bool isQuit() to static bool isQuit() which checks it's inputs for for isQuit()
        * Feared there might be a problem since inputs have isQuit() and UserInput has isQuit(), but no errors given
        * %X% The app crashed just like when I made the changes previously
          * I found the problem was in UserInput::isQuit()
          * Since the subclasses had isQuit() but UserInput also had a static isQuit() it crashed
          * %Y% FIXED: Renamed subclass isQuit() to getQuit() (less intuitive) and added virtual bool getQuit() to UserInput
    * Now checks both inputs for "quit" - w00t
    * Still need to clean-up !TenMilManUI::run() but the worst of it is over
    * NOTE: I'll need to do the same thing I did for isQuit/getQuit for update()

  * TODO:
    * %Y% Remove select from !SDLMouseInput, implement in SelectManager instead
    * %Y% Add HOVER\_IN, HOVER\_OUT and HOVER\_MOVE to the events that are detected and dispatched
    * Make UserInput handle multiple inputs
### Tues 10/16/07 ###
  * Created InteractiveRectangle which subclasses !UIComponent
    * Hopefully this will allow me to create and test event handler code
    * Test program doesn't run, although it does compile successfully
  * Made !UIComponent a subclass of EventHandler
    * This will handle the basic events that all basic controls will have
    * Changed EventHandler::getObjectID() to EventHandler::getEvtHandlerID() because there was ambiguity
  * Added names for events to !UIComponent
    * In !UIComponent.h
      * static std::string ~event name~
    * In !UIComponent.cpp
      * std::string !UIComponent::~event name~ = "~event name~";
  * Got the SelectManager working as desired, but object info is incorrect -> !GetW() and !GetH() are returning 10
    * Tracked the problem down to the DisplayObject class
      * DisplayObject constructor sets w and h to 10, always
      * FIX: Went higher up to the first class that specified w & h in the constructor, DisplayObjectContainer - specified that it use the w & h arguments to actually set the values
  * Modified SelectManager
    * Added the ability to dispatch multiple events { UNPRESS == CLICK, so dispatch both }
    * Modified PRESS events so only "detected" if the last event wasn't a press
  * Created test class "InteractiveRectangle" for testing event handlers
    * Successfully tested PRESS, UNPRESS and CLICK events
  * TODO:
    * Remove select from !SDLMouseInput, implement in SelectManager instead
    * Add HOVER\_IN, HOVER\_OUT and HOVER\_MOVE to the events that are detected and dispatched

### Mon 10/15/07 ###
  * Working on understanding EventHandlers
    * SelectManager registers UIComponents; unfortunately, all the things that can be displayed (currently) aren't derived from UIComponent
    * I'll talk with Peter about it more later, instead of implementing handleEvent (since I can't easily test it, I'll work on SelectManager::update() to encompass more events besides selection)
  * SelectManager::update()
    * Added logic to also handle "PRESS" events (OnMouseDown equivalent)
    * Added map<int,UIComponent>pressedObjects to keep track of pressed objects as well
    * TODO: Add logic to add/remove items from the selected(&pressed) objects maps
  * objs -> obj in SelectManager
    * Modified so instead of a stack of objects, only one is checked the "top" graphically
    * NOTE: The "top" graphically depends on the order the objects are registered to the SelectManager, it's assumed that they'll be registered on instantiation.
  * After making the objs->obj change in SelectManager, I tried to run the test app - it doesn't appear to run anymore...
  * TODO:
    * objs -> obj in SelectManager
    * Modify for dispatching multiple events in SelectManager
    * Create a test class for testing EventHandler
### Fri 10/12/07 ###
  * Modifying UserInput
    * Make multiple instantiation of UserInput possible (remove singleton-ness)
      * Change w/o making it incompatible with current test program
      * UserInput now contains set<UserInput> inputs which keeps track of all UserInputs
      * isCreated and inst variables from UserInput will now be part of the subclasses, since they'll be singletons
      * getX() and all accessor functions are now implemented in the subclasses, but they'll need to be specified in the UserInput class
      * UserInput::instance() now retrieves the first UserInput in the set UserInput::inputs
      * !SDLMouseInput::createInstance() handles !SDLMouseInput static vars and adds itself to UserInput::inputs
    * Finished moving info from InputData to UserInput subclasses
  * Modifying SelectManager
    * Update SelectManager::update() to deal with modified UserInput class
    * SelectManager::update() now works with modified UserInput class, but there'll be problems with advanced behavior (only checks a couple things for equivalence right now) as it is
      * Checks for equivalent events via x,y,pressed & select -> what will happen for special table events?
  * Create TableInput : UserInput
    * Made basic setup for getting events from the table
    * Forgot that quitting was done through UserInput, without TableInput having a "quit" you can't quit; had to kill from pitfall
### Wed 10/10/07 ###
  * Subclassed InputData class in UserInput.cpp, original InputClass should be sufficient for the mouse
    * InputData
      * ADDED side\_id
    * GestureData
      * INHERITS x,y (starting point)
      * ADDED gestureStr (string containing the sequence of the gesture ex. "LDUR")
    * RealTimeData
      * INHERITS x,y {starting point, center point} (depending on event type)
      * ADDED evtType { "DRAG", "ROTATE", "ZOOM" }
      * ADDED amt     {   dist,    angle,  scale }
  * Modified UserInput
    * ADDED getSide()
    * ADDED getClass() { MOUSE, GESTURE, REALTIME }
  * Event class will need the same info as InputData, do we need a new class?
    * #define Event InputData%BR%
      1. efine GestureEvent GestureData%BR%
      1. efine RealTimeEvent RealTimeData
  * Work on SelectManager
    * Updated SelectManager::update() to get input from UserInput and check if it's repeated input
    * Processes select event to objects at (x,y)
  * Moved select from InteractiveObject to UIComponent
  * Worked on implementing EventHandler::process(Event evt)
    * Successfully added to component and called on select
    * Problem: Event doesn't contain a target object, should add that
    * Talked to Peter, apparently, controls are going to be subclasses of EventHandlers as well
      * With this setup, what should EventHandlers be registered with the !UIComponent since the UIComponent is an EventHandler?
  * Removed InputData, GestureData and RealTimeData classes
    * Will need to re-work how data is Xfered then
  * TODO:
    * Implement EventHandler::process(Event evt)
### Mon 10/8/07 ###
  * Moved classes to TenUI namespace
    * Managers
    * Event, EventHandler, EventDispatcher
  * Removed InteractiveObject
  * Discussed new structure of InputData with Thomas
    * Decided to subclass into RealTimeData, GestureData, MouseData(?)
  * TODO:
    * Implement EventHandler::process(Event evt)
    * Update UserInput to deal with data for new architecture
    * Update Event to handle necessary data
    * Talk to Peter about necessity of DragManager

### Fri 10/5/07 ###
  * Working on manager related stuff
    * Modified definition so managers now deal with !UIComponents instead of InteractiveObjects
    * Implementing SelectManager::update function
      * Checks for chg in UserInput
      * If chg = select => package
      * Get objects that are at pt (x,y)
      * See which if any are registered with the manager
      * If registered, tell them to process the event
    * Implementing InteractiveObject::select(Event evt) function
      * Takes event, get event handlers for evt->evtName
      * Process all event handlers for evtName
    * Made DisplayObject a subclass of EventDispatcher
  * TODO:
    * Implement EventHandler::process(Event evt)
    * Update UserInput to deal with data for new architecture
    * Update Event to handle necessary data