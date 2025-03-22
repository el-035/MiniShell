#include "minishell.h"

static int	ft_word_count(char *s)
{
	int	i;
	int	wc;
	int	f_quote;

	i = 0;
	wc = 0;
	f_quote = 0;
	while (s[i])
	{
		while ((s[i] == 32 || s[i] == 9) && !f_quote)
			i++;
		if (s[i] && !f_quote)
		{
			wc++;
			if (s[i] == 34 || s[i] == 39)
				f_quote = s[i++];
		}
		while (s[i] && (f_quote || (s[i] != 32 && s[i] != 9)))
		{
			if (f_quote && s[i] == f_quote)
				f_quote = 0;
			i++;
		}
	}
	return (wc);
}

static char word_len(char *s, int i)
{
	int		j;
	int		f_quote;
	int		len;

	j = 0;
	f_quote = 0;
	if (s[i] == 34 || s[i] == 39)
	{
		j++;
		f_quote = s[i++];
	}
	while(s[i])
	{
		if ((f_quote == 0 && (s[i] == 32 || s[i] == 9)) || f_quote == s[i])
			break ;
		i++;
		j++;
	}
	len = j + 1;
	if (f_quote == 0)
		len--;
	return (len);
}

static char	*ft_word(char *s, int i)
{
	char	*word;
	int		j;
	int		len;

	while ((s[i] == 32 || s[i] == 9) && s[i])
		i++;
	len = word_len(s, i);
	word = (char *) ft_calloc((len + 1), sizeof(char));	//ft_calloc
	if (!word)
		return (NULL);
	j = 0;
	while (j < len)
		word[j++] = s[i++];
	return (word);
}

/* static char	**free_split(char **split)
{
	int	word;

	word = 0;
	while (split[word])
	{
		free(split[word]);
		word++;
	}
	free(split);
	return (NULL);
} */

char	**mini_split(char const *s)	//remove mains
{
	int		wc;
	int		i;
	int		j;
	char	**split;

	wc = ft_word_count((char *) s);
	i = 0;
	j = 0;
	split = (char **) ft_calloc ((wc + 1), sizeof(char *));
	if (!split)
		return (NULL);

	while (s && split && j < wc)
	{
		split[j] = ft_word((char *)s, i);
		if (!split[j++])
			return (free_split(split), NULL);
		while ((s[i] == 32 || s[i] == 9) && s[i])
			i++;
		i = i + ft_strlen(split[j - 1]);
	}
	split[j] = 0;
	return (split);
}

/* int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Please provide a string to split.\n");
        return 1;
    }

    char **result = mini_split(argv[1]);
    if (!result)
        return 1;

    int i = 0;
    while (result[i])
    {
        printf("Token %d: %s\n", i, result[i]);
        i++;
    }
    // Free memory
    i = 0;
    while (result[i])
        free(result[i++]);
    free(result);

    return 0;
} */
/* 
int main(void)
{
    char *input = " 'cazzos' a test";
    char **result = mini_split(input);
    int i = 0;

    if (!result)
        return (1);
    while (result[i])
    {
        printf("Token %d: %s\n", i, result[i]);
        i++;
    }
    // Free the result if needed
    i = 0;
    while (result[i])
        free(result[i++]);
    free(result);
    return (0);
}

 */
/* 
 void print_test_result(char *test_case, int test_num, int result) {
    if (result) {
        // Green for OK
        printf("\033[0;32mcorrect tests/total tests\033[0m\n");
    } else {
        // Red for KO
        printf("\033[0;31mwrong tests/total tests\033[0m\n");
        printf("Test %d: %s\n", test_num, test_case);
    }
}

int main() {
    // Example test cases (You can adjust the expected results here)
    char *test_cases[] = {
        "hello world",                // Simple case with space
        "  hello   world  ",          // Leading/trailing and multiple spaces
        "hello",                      // Single word, no spaces
        "  hello",                    // Leading space
        "hello  ",                    // Trailing space
        "hello  world",               // Multiple spaces in between
        "hello 'world'",              // Single quote around world
        "\"hello world\"",            // Double quotes around the phrase
        "'hello world'",              // Single quotes around the phrase
        "\"hello\" \"world\"",        // Double quotes around each word
        "'hello' 'world'",            // Single quotes around each word
        "  'hello'   \"world\" ",     // Mixed single and double quotes with spaces
        "   'hello world'   ",        // Single quoted phrase with leading/trailing spaces
        "  hello \"world foo\" bar ", // Quotes in the middle with other words
        "\"hello\" world \"foo bar\"",// Quotes in the middle of sentence
        "'hello world' foo 'bar'",    // Mixed single quotes with spaces
        "  \"hello world\"  ",        // Double quotes with spaces around
        "hello world'foo'bar",        // Single quote inside the word
        "    \"hello\"   \"world\"    ", // Extra spaces and double quotes
        "hello\\\"world",              // Backslash handling (to test escaping)
        "    hello     world   ",     // Leading and trailing spaces
        "\"foo bar\"  \"baz\"",       // Double quotes with multiple words
        "'foo' \"bar\" 'baz'",        // Mixed quotes and spaces
        "hello 'world' foo",          // Quote within a sentence
        "\"double quotes\" inside",  // Double quotes with word inside
        "abc 'quoted string' 123",    // Mixed quoted string and regular words
        "\"hello\" inside",           // Single word with double quotes around
        "'quoted' space 'example'",   // Multiple quoted words
        "  'extra'   spaces  ",       // Quoted word with extra spaces
        "\"test\" space \"again\"",   // Quotes with spaces between
        "no quotes here",             // No quotes
        "\"no space\"",               // No space inside quotes
        "'quoted word' notquoted",    // Mixed quoted and unquoted words
        "quote 'test\" test'",        // Quotes with inner quotes
        "empty  '   quoted  ' word",  // Empty quoted with spaces
        " 'quote' and more words",    // Mixed quoted words with space
        "   \"\" double quote",       // Double empty quotes
        "random \" words  with \"",  // Quotes in the middle
        "complex \"testing\" here",   // Quotes with complex sentence
        "\"start quotes and space\" text",  // Starting with quote and spaces
        "'quote \"inside\" double quotes'", // Mixed nested quotes
        "a 'hello world' test",       // Test for nested quotes
        "\"escaping\\\"chars\"",      // Escaping quotes inside
        "more    'quoted words'  now", // More complex cases
        "spaced    \"words inside\" again",  // Extra spaces between words
        "no quotes no spaces",        // Simple no-space case
        " \"quoted words\"\" again\"", // Handling multiple quotes correctly
        "mix 'quoted' and unquoted",  // Mixed quotes with space
        "final case \"with double quotes\""
    };

    // Expected results for each case, modify as needed
    int expected_results[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };

    int total_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    int correct_tests = 0;
    int wrong_tests = 0;

    // Loop through each test case
    for (int i = 0; i < total_tests; i++) {
        char **split = mini_split(test_cases[i]);

        // Here you would compare the split result to the expected result
        // for now it's set to compare with the expected results array
        int result = 0;
        
        // Add logic to compare split[] with the expected result
        result = expected_results[i];  // Update this logic as needed.

        if (result) {
            correct_tests++;
        } else {
            wrong_tests++;
            // Print the test case with the "wrong" result
            printf("\033[0;31mTest %d: %s\033[0m\n", i + 1, test_cases[i]);
        }

        // Free the memory allocated by mini_split
        if (split != NULL) {
            free_split(split);
        }
    }

    // Print summary
    if (wrong_tests == 0) {
        printf("\033[0;32m%d correct tests / %d total tests\033[0m\n", correct_tests, total_tests);
    } else {
        printf("\033[0;31m%d wrong tests / %d total tests\033[0m\n", wrong_tests, total_tests);
    }

    return 0;
} */