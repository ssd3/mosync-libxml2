#include <MAUtil/String.h>
#include <MAUtil/Moblet.h>
#include <conprint.h>
#include "libxml2/include/libxml/HTMLparser.h"

using namespace MAUtil;

/**
 * A Moblet is a high-level class that defines the
 * behaviour of a MoSync program.
 */
class MyMoblet : public Moblet
{
public:
	/**
	 * Initialize the application in the constructor.
	 */
	MyMoblet()
	{
		htmlParserCtxtPtr parser = htmlCreatePushParserCtxt(NULL, NULL, NULL, 0, NULL, (xmlCharEncoding)0);
		htmlCtxtUseOptions(parser, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
		MAUtil::String htmlData = "<div id=\"content\"><div class=\"post\"><h2 class=\"post-title\"><a href=\"http://feinan.com/2011/09/29/parsing-xhtml-in-c-%e2%80%93-a-libxml2-tutorial/\" title=\"Parsing (X)HTML in C – A libxml2 tutorial\">Parsing (X)HTML in C – A libxml2 tutorial</a></h2><p class=\"post-date\"><span class=\"day\">29</span> <span class=\"month\">Sep</span> <span class=\"year\">2011</span> <span class=\"postcomment\"><a href=\"http://feinan.com/2011/09/29/parsing-xhtml-in-c-%e2%80%93-a-libxml2-tutorial/#disqus_thread\" title=\"Comment on Parsing (X)HTML in C – A libxml2 tutorial\" data-disqus-identifier=\"54 http://feinan.com/2011/09/29/parsing-xhtml-in-c-%e2%80%93-a-libxml2-tutorial/\">1 Comment</a></span></p>";
		// Last argument is 0 if the web page isn’t complete, and 1 for the final call.
		htmlParseChunk(parser, htmlData.c_str(), htmlData.length(), 0);
		walkTree(xmlDocGetRootElement(parser->myDoc));
		printf("Press zero or back to exit\n");
	}

	void walkTree(xmlNode * a_node)
	{
	  xmlNode *cur_node = NULL;
	  xmlAttr *cur_attr = NULL;
	  for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
	     // do something with that node information, like… printing the tag’s name and attributes
	    printf("Got tag : %s\n", cur_node->name);
	    for (cur_attr = cur_node->properties; cur_attr; cur_attr = cur_attr->next) {
	      printf(" -> with attribute : %s\n", cur_attr->name);
	    }
	    walkTree(cur_node->children);
	  }
	}

	/**
	 * Called when a key is pressed.
	 */
	void keyPressEvent(int keyCode, int nativeCode)
	{
		if (MAK_BACK == keyCode || MAK_0 == keyCode)
		{
			// Call close to exit the application.
			close();
		}

		// Print the key character.
		printf("You typed: %c\n", keyCode);
	}

	/**
	 * Called when a key is released.
	 */
	void keyReleaseEvent(int keyCode, int nativeCode)
	{
	}

	/**
	 * Called when the screen is touched.
	 */
	void pointerPressEvent(MAPoint2d point)
	{
		// Print the x and y coordinate.
		printf("You touched: %i %i\n", point.x, point.y);
	}
};

/**
 * Entry point of the program. The MAMain function
 * needs to be declared as extern "C".
 */
extern "C" int MAMain()
{
	Moblet::run(new MyMoblet());
	return 0;
}
