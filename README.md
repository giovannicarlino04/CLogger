C Logger without std libraries

Okay so I had this idea of a full fledged logger, which has it's own low-level printing mechanism and uses NO stdlibc at ALL!!!

HOW IT WORKS:
	The only important function AS OF NOW is the "log" function (duh...), it has two arguments, the first one is the message to print, the second one is the log type (it can be either LOG_LEVEL_INFO (0), LOG_LEVEL_WARNING (1), LOG_LEVEL_ERROR (3))

DEFAULT COLORS:
	GREEN for info
	YELLOW for warning
	RED for error

LICENSE: 
	MIT