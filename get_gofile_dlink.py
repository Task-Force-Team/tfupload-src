import json
from sys import argv

def parse(json_data):
    # Parse JSON data
    data = json.loads(json_data)

    # Extract the download page URL
    download_page = data['data']['downloadPage']

    # Print the download link
    print(f"Download link: {download_page}")

# define the interpoint
def parse_intro(arg, data):
    if arg == "parse":
        parse(data)
    else:
        print("Bad Argument!")

if __name__ == "__main__":
    if len(argv) < 3:
        print("Usage: python3 get_gofile_dlink.py parse '{\"data\":{\"downloadPage\":\"...\"}}'")
    else:
        parse_intro(argv[1], " ".join(argv[2:]))
