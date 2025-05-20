#pragma once

namespace NP
{
	class String
	{
	private:
		char* data;
		size_t length;

	public:
        // Constructors
        String();                     // Default constructor
        String(const char* str);      // Constructor from C-string
        String(const String& other);  // Copy constructor

        // Destructor
        ~String();

        // Assignment operator
        String& operator=(const String& other);
        char operator[](size_t index) const;           // Access character
        String operator+(const String& other) const;   // Concatenation
        bool operator==(const String& other) const;    // Equality
        bool operator!=(const String& other) const;    // Inequality
        bool operator<(const String& other) const;     // Less than
        bool operator>(const String& other) const;     // Greater than

        // Basic operations
        size_t getLength() const;                           // Get string length
        const char* getCString() const;                     // Get C-string representation
        char charAt(size_t index) const;                    // Get character at index
        int compare(const String& other) const;             // Compare strings
        bool equals(const String& other) const;             // Check equality
        bool isEmpty() const;                               // Check if empty
        String substring(size_t start, size_t end) const;   // Extract substring
	};
}