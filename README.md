Here is a simple `README.md` file template for your GitHub repository:


# TimeRoom_md5_cracker

## Description

TimeRoom_md5_cracker is a tool designed to crack MD5 hashes by matching them with a list of passwords. It compares the MD5 hashes from a given file with a list of potential passwords, and prints the matching passwords along with the associated hash.

## Install

To install and set up the project, follow these steps:

1. Clone the repository:

   ```bash
   git clone https://github.com/Aziz-Omar-13/TimeRoom_md5_cracker.git
   ```

2. Change directory to the project folder:

   ```bash
   cd TimeRoom_md5_cracker
   ```

3. Compile the C program:

   ```bash
   gcc -o TimeRoom_md5_cracker TimeRoom_md5_cracker.c -lssl -lcrypto
   ```

## Usage

Once compiled, you can use the tool with the following commands:

1. To crack hashes with a hash file and a password file:

   ```bash
   ./TimeRoom_md5_cracker -H <hashfile> -P <passwordfile>
   ```

2. To crack a single hash with a single password:

   ```bash
   ./TimeRoom_md5_cracker -h <hash> -p <password>
   ```

### Example:

```bash
./TimeRoom_md5_cracker -H hashes.txt -P passwords.txt
```

This command will read the MD5 hashes from `hashes.txt` and attempt to crack them using the passwords in `passwords.txt`.

## Requirements

- Linux-based OS (Kali Linux recommended for CTF/penetration testing)
- OpenSSL libraries (`libssl` and `libcrypto`)
- GCC compiler

## License

This project is open-source and available under the [MIT License](LICENSE).
```

Feel free to update any sections as necessary for your project specifics! This `README.md` provides installation, usage instructions, and some basic project details for GitHub.
