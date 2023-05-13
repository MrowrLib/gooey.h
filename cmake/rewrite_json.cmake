# Read the JSON file
file(READ ${JSON_FILE} JSON_CONTENT)

# Output the JSON
message(STATUS "JSON content: ${JSON_CONTENT}")

# Modify the JSON content
# string(REGEX REPLACE "\"application-binary\"\\s*:\\s*\"[^\"]+\"" "\"application-binary\": \"${NEW_VALUE}\"" JSON_CONTENT_MODIFIED "${JSON_CONTENT}")
# string(REGEX REPLACE "(\"application-binary\"\\s*:\\s*\")[^\"]*(\")" "\\1${NEW_VALUE}\\2" JSON_CONTENT_MODIFIED ${JSON_CONTENT})
# string(REGEX REPLACE "(\"application-binary\"\\s*:\\s*\")[^\"]*(\",?)" "\\1${NEW_VALUE}\\2" JSON_CONTENT_MODIFIED ${JSON_CONTENT})
string(REGEX REPLACE "(\"application-binary\": \")[^\"]*(\")" "\\1${NEW_VALUE}\\2" JSON_CONTENT_MODIFIED "${JSON_CONTENT}")

# Output the modified JSON
message(STATUS "Modified JSON content: ${JSON_CONTENT_MODIFIED}")

message(STATUS "JSON_FILE: ${JSON_FILE}")

# Write the modified JSON content back to the file
file(WRITE ${JSON_FILE} "${JSON_CONTENT_MODIFIED}")
