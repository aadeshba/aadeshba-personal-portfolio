compile using make 

run as follows--   ./rsa [prime1] [prime2]

there are three options:

Exit-- EXIT    -- terminates the program *gracefully*
Encrypt-- ENCRYPT [output file] [n] [message]
Decrypt-- DECRYPT [encrypted file] [output file]

The encrypted file to be called in Decrypt command is likely the output file from the initial encrypt call.

n must equal prime1 * prime2 in any call of encrypt. To decrypt that same file, must use same p and q values.

