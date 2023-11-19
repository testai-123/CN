import socket

def ip_to_hostname(ip_address):
    try:
        hostname, _, _ = socket.gethostbyaddr(ip_address)
        return hostname
    except socket.herror:
        return "No hostname found for this IP address"

def hostname_to_ip(hostname):
    try:
        ip_address = socket.gethostbyname(hostname)
        return ip_address
    except socket.gaierror:
        return "No IP address found for this hostname"

def main():
    while True:
        print("1. IP to Hostname")
        print("2. Hostname to IP")
        print("3. Quit")
        choice = input("Choose an option (1/2/3): ")

        if choice == "1":
            ip_address = input("Enter an IP address: ")
            hostname = ip_to_hostname(ip_address)
            print("Hostname:", hostname)
        elif choice == "2":
            hostname = input("Enter a hostname (URL): ")
            ip_address = hostname_to_ip(hostname)
            print("IP Address:", ip_address)
        elif choice == "3":
            print("program exit!")
            break
        else:
            print("Invalid choice. Please choose 1, 2, or 3.")

if __name__ == "__main__":
    main()
