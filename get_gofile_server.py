import requests
import json

def get_gofile_server():
    url = "https://api.gofile.io/getServer"
    response = requests.get(url)
    if response.status_code == 200:
        data = response.json()
        if data["status"] == "ok":
            return data["data"]["server"]
    return None

if __name__ == "__main__":
    server = get_gofile_server()
    if server:
        print(server)
    else:
        print("Failed to get server from Gofile API")
