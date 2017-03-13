#include <stdio.h>
#include <stdlib.h>
#include <glib-object.h>
#include <json-glib/json-glib.h>

int
main (int argc, char *argv[])
{
  JsonParser *parser;
  JsonNode *root;
  GError *error;

  if (argc < 2)
  {
    g_print ("Usage: test <filename.json>\n");
    return EXIT_FAILURE;
  }

  parser = json_parser_new ();

  error = NULL;
  json_parser_load_from_file (parser, argv[1], &error);
  if (error)
  {
		g_print ("Unable to parse `%s': %s\n", argv[1], error->message);
    g_error_free (error);
    g_object_unref (parser);
    return EXIT_FAILURE;
  }

  root = json_parser_get_root (parser);

	JsonNode *result;
	result = json_path_query ("$.store..author", root, NULL);

	if (result)
	{
		JsonArray *array = json_node_get_array (result);
		JsonNode *child = json_array_get_element (array, 0);
		
		const char *content  = json_node_get_string (child);
		printf ("content: %s\n", content);

		/* Json-CRITICAL **: 
		 * json_node_set_string: assertion '!node->immutable' failed */
		/* Couldn't change value of the child node */ 
		json_node_set_string (child, "NewName");
	}
 	
  return EXIT_SUCCESS;
}
