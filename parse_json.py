import sys
import json

def parse_json(json_response):
    try:
        response = json.loads(json_response)
        file_id = response.get('id')
        if file_id:
            download_link = f"https://pixeldrain.com/u/{file_id}"
            print(f"Download link: {download_link}")
        else:
            print("File ID not found in JSON response.")
    except json.JSONDecodeError as e:
        print(f"Failed to parse JSON response: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python parse_json.py <json_response>")
        sys.exit(1)

    json_response = sys.argv[1]
    parse_json(json_response)
