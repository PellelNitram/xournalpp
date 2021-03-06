-- This is an example Xournal++ Plugin - copy this to get started

var_dump = require "var_dump"

-- Register all Toolbar actions and intialize all UI stuff
function initUi()
  print("Hello from Example: Plugin initUi called\n");

  ref = app.registerUi({["menu"] = "Test123", ["callback"] = "exampleCallback"});
  print("Menu reference:");
  var_dump(ref);

  print("Example plugin registered\n");
end

-- Callback if the menu item is executed
function exampleCallback()
  app.msgbox("Test123", "yes,no");
end
