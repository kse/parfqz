/*
 * Main file which handles the threading and binds everything together
 *
 * Copyright (c) 2014 Rune M. Friborg <rune.m.friborg@gmail.com>.
 * See LICENSE.txt for licensing details (GPGv2 License). 
 * */

#include <stdlib.h>
#include <argp.h>

const char *argp_program_version =
  "parfqz 0.1";
const char *argp_program_bug_address =
  "<rune.m.friborg@gmail.com>";

/* Program documentation. */
static char doc[] =
  "parfqz -- Best fastqz compression/decompression tool";

/* A description of the arguments we accept. */
static char args_doc[] = "FILE";

/* The options we understand. */
static struct argp_option options[] = {
  {"compress",  'c', 0,      0,  "Compress FILE or from STDIN(default)" },
  {"decompress",  'd', 0,      0,  "Decompress FILE or from STDIN" },
  {"verbose",  'v', 0,      0,  "Produce verbose output" },
  //  {"quiet",    'q', 0,      0,  "Don't produce any output" },
  //  {"silent",   's', 0,      OPTION_ALIAS },
  {"output",   'o', "FILE", 0,
   "Output to FILE instead of STDOUT" },
  { 0 }
};

/* Used by main to communicate with parse_opt. */
struct arguments
{
  char *args[1];                /* FILE */
  int silent, verbose, compress;
  char *output_file;
};

/* Parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;

  switch (key)
    {
      //    case 'q': case 's':
      //      arguments->silent = 1;
      //      break;
    case 'v':
      arguments->verbose = 1;
      break;
    case 'c':
      arguments->compress = 1;
      break;
    case 'd':
      arguments->compress = 0;
      break;
    case 'o':
      arguments->output_file = arg;
      break;

    case ARGP_KEY_ARG:
      if (state->arg_num >= 1)
        /* Too many arguments. */
        argp_usage (state);

      arguments->args[state->arg_num] = arg;

      break;

    case ARGP_KEY_END:
      if (state->arg_num < 0)
        /* Not enough arguments. */
        argp_usage (state);
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };

int
main (int argc, char **argv)
{
  struct arguments arguments;

  /* Default values. */
  arguments.verbose = 0;
  arguments.output_file = "-";
  arguments.compress = 1;
  arguments.args[0] = "-";



  /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

 
  
  splitstream(arguments.args[0]);
  
  


  printf ("FILE = %s\nOUTPUT_FILE = %s\n"
          "VERBOSE = %s\nSILENT = %s\n",
          arguments.args[0],
          arguments.output_file,
          arguments.verbose ? "yes" : "no",
          arguments.silent ? "yes" : "no");

  exit (0);
}
