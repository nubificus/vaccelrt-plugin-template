#include <stdio.h>

#include <vaccel.h> /* needed for vAccel specific structures (eg Session */
#include <plugin.h> /* needed for register_plugin_functions */

/* A function that will be mapped to a vAccel User API operation using
 * register_plugin_functions() */
static int my_noop_function(struct vaccel_session *sess)
{
	fprintf(stderr, "[my noop function] session: %d\n", sess->session_id);

	return VACCEL_OK;
}

/* An array of the operations to be mapped */
struct vaccel_op ops[] = {
	VACCEL_OP_INIT(ops[0], VACCEL_NO_OP, my_noop_function),
};

/* The init() function, called upon plugin initialization */
static int init(void)
{
	/* This is where the static function above `my_noop_function()`
	 * gets mapped to the relevant vAccel User API operation. */
	return register_plugin_functions(ops, sizeof(ops) / sizeof(ops[0]));
}

/* The fini() function, called before unloading the plugin */
static int fini(void)
{
	return VACCEL_OK;
}

VACCEL_MODULE(
	.name = "vAccel template plugin",
	.version = "0.9",
	.init = init,
	.fini = fini
)
