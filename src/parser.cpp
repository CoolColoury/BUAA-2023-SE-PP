#include "parser.h"
#include "error.h"

void Parser::parse(int argc, char* argv[])
{
    check_args_error(argc, argv);
    parse_arg(argc, argv);
    std::ifstream f;
    f.open(m_filename);
    if (!f)
    {
        throw missing_file();
    }
    parse_words(f);
}

void Parser::parse_arg(int argc, char* argv[])
{
    for (int arg_i = 0; arg_i < argc; arg_i++)
    {
        if (strcmp(argv[arg_i], "-n") == 0)
        {
            m_config.type = 'n';
            arg_i += 1;
            m_filename = argv[arg_i];
        }
        else if (strcmp(argv[arg_i], "-w") == 0)
        {
            m_config.type = 'w';
            arg_i += 1;
            m_filename = argv[arg_i];
        }
        else if (strcmp(argv[arg_i], "-c") == 0)
        {
            m_config.type = 'c';
            arg_i += 1;
            m_filename = argv[arg_i];
        }
        else if (strcmp(argv[arg_i], "-h") == 0)
        {
            arg_i += 1;
            m_config.head = (char) tolower(argv[arg_i][0]);
        }
        else if (strcmp(argv[arg_i], "-t") == 0)
        {
            arg_i += 1;
            m_config.tail = (char) tolower(argv[arg_i][0]);
        }
        else if (strcmp(argv[arg_i], "-j") == 0)
        {
            arg_i += 1;
            m_config.n_head = (char) tolower(argv[arg_i][0]);
        }
        else if (strcmp(argv[arg_i], "-r") == 0)
        {
            m_config.enable_loop = true;
        }
    }
}

void Parser::check_args_error(int argc, char* argv[])
{
    Config config;

    // TODO
    for (int arg_i = 0; arg_i < argc; ++arg_i)
    {
        if (strcmp(argv[arg_i], "-n") == 0 ||
            strcmp(argv[arg_i], "-w") == 0 ||
            strcmp(argv[arg_i], "-c") == 0)
        {
            arg_i++;
            check_bound(arg_i, argc, argv[arg_i - 1]);
            check_conflicted_argument(config.type);
            check_filename(argv[arg_i]);
            config.type = argv[arg_i - 1][1];
        }
        else if (strcmp(argv[arg_i], "-h") == 0)
        {
            arg_i++;
            check_bound(arg_i, argc, argv[arg_i - 1]);
            check_conflicted_argument(config.head);
            check_is_single_alpha(argv[arg_i]);
            config.head = (char) tolower(argv[arg_i][0]);
        }
        else if (strcmp(argv[arg_i], "-t") == 0)
        {
            arg_i++;
            check_bound(arg_i, argc, argv[arg_i - 1]);
            check_conflicted_argument(config.tail);
            check_is_single_alpha(argv[arg_i]);
            config.tail = (char) tolower(argv[arg_i][0]);
        }
        else if (strcmp(argv[arg_i], "-j") == 0)
        {
            arg_i++;
            check_bound(arg_i, argc, argv[arg_i - 1]);
            check_conflicted_argument(config.n_head);
            check_is_single_alpha(argv[arg_i]);
            config.n_head = (char) tolower(argv[arg_i][0]);
        }
        else if (strcmp(argv[arg_i], "-r") == 0)
        {
            check_conflicted_argument(config.enable_loop);
            config.enable_loop = true;
        }
        else
        {
            check_unexcepted_argument(argv[arg_i]);
        }
    }
    check_config_valid(config);
}

void Parser::parse_words(std::istream& f)
{
    std::string buf;
    stream_read_string_reverse(f, buf);

    std::string word;
    for (auto it = buf.begin(), end = buf.end(); it != end; ++it)
    {
        if (std::isalpha(*it))
        {
            word += *it;
        }
        else
        {
            if (!word.empty())
            {
                m_words.push_back(word);
                word = std::string();
            }
        }
    }
    if (!word.empty())
    {
        m_words.push_back(word);
    }
}

void stream_read_string_reverse(std::istream& f, std::string& result)
{
    f.seekg(0, std::istream::end);
    std::streamoff len = f.tellg();
    f.seekg(0);
    if (len > 0)
    {
        result.reserve(static_cast<std::string::size_type>(len));
    }
    result.assign(std::istreambuf_iterator<char>(f.rdbuf()),
        std::istreambuf_iterator<char>());
}