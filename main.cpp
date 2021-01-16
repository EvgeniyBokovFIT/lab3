#define _CRT_SECURE_NO_WARNINGS
#include "optionparser.h"
#include "Header.h"

struct Arg : public option::Arg
{
    

    static option::ArgStatus Unknown(const option::Option& option, bool msg)
    {
        if (msg)
        {
            cout << "Unknown option '" << option.name <<"'"<< endl;
            
        }
        return option::ARG_ILLEGAL;
    }

    static option::ArgStatus Numeric(const option::Option& option, bool msg)
    {
        char* endptr = 0;
        if (option.arg != 0 && strtol(option.arg, &endptr, 10))
        {
        };
        if (endptr != option.arg && *endptr == 0)
            return option::ARG_OK;

        if (msg)
        {
            cout<<"Option '"<< option << "' requires a numeric argument" << endl;
        }
        return option::ARG_ILLEGAL;
    }
};

enum optionIndex
{
    Unknown,
    Help,
    FirstGamer,
    SecondGamer,
    Rounds
};
const option::Descriptor usage[] = {
        {Unknown, 0, "",  "",       Arg::Unknown,  "USAGE: example_arg [options]\n\n"
                                                   "Options:"},
        {Help,    0, "h",  "help",   Arg::None,     "  \t--help  \tYou can choose the type of two players and the number of rounds in the series. Total player types 3:\n\t\t\tRandom - random player.\n\t\t\tOptimal - clever player ;\n\t\t\t Interactive - it's are you;) .\t"},
        {FirstGamer,   0, "f", "first",  Arg::Optional, "  -f[/Optimal/Interactive/Random], \t--first[/Optimal/Interactive/Random]"
                                                   "  \tType of first player. Default is Random."},
        {SecondGamer,  0, "s", "second", Arg::Optional, "  -s[/Optimal/Interactive/Random], \t--second[/Optimal/Interactive/Random]"
                                                   "  \tType of second player. Default is Random."},
        {Rounds,   0, "c", "count",  Arg::Numeric,  "  -c <num>, \t--count=<num>  \tNumber of rounds in a series. Default is 1."},
        {0,       0, 0,   0,        0,             0} };

int main(int argc, char* argv[])
{
    argc -= (argc > 0);
    argv += (argc > 0); 
    option::Stats stats(usage, argc, argv);

    vector<option::Option> options(stats.options_max);
    vector<option::Option> buffer(stats.buffer_max);


    option::Parser parse(usage, argc, argv, options.data(), buffer.data());
    if (parse.error())
        return 1;

    if (options[Help] || argc == 0)
    {
        int columns = getenv("COLUMNS") ? atoi(getenv("COLUMNS")) : 80;
        option::printUsage(fwrite, stdout, usage, columns);
        return 0;
    }

    if (options[Unknown])
        return 0;

    if (parse.nonOptionsCount() > 0)
    {
        for (int i = 0; i < parse.nonOptionsCount(); ++i)
            cout << "Unknown argument #" << i << " is " << parse.nonOption(i) << endl;
        return 0;
    }

    int rounds = 1;
    GamerType f = GamerType::Random, s = GamerType::Random;

    if (options[Rounds])
    {
        rounds = atoi(options[Rounds].arg);
    }

    if (options[FirstGamer])
    {
        if (((string)"Random") == options[FirstGamer].arg)
            f = GamerType::Random;
        else if (((string)"Optimal") == options[FirstGamer].arg)
            f = GamerType::Optimal;
        else if (((string)"Interactive") == options[FirstGamer].arg)
            f = GamerType::Interactive;
        else
        {
            fprintf(stdout, "Unknown player type: %s!", options[FirstGamer].arg);
            return 0;
        }
    }

    if (options[SecondGamer])
    {
        if (((string)"Random") == options[SecondGamer].arg)
            s = GamerType::Random;
        else if (((string)"Optimal") == options[SecondGamer].arg)
            s = GamerType::Optimal;
        else if (((string)"Interactive") == options[SecondGamer].arg)
            s = GamerType::Interactive;
        else
        {
            fprintf(stdout, "Unknown player type: %s!", options[SecondGamer].arg);
            return 0;
        }
    }
    try
    {
        play(rounds, f, s);
    }
    catch (const char* ex)
    {
        cout << ex;
    }
    
}
