def is_valid_IPv4(ip):
    
    segments = ip.split('.')
    return len(segments) == 4 and all(segment.isdigit() and 0<= int(segment) <= 255 for segment in segments)
    
def get_subnet_mask(class_check):
    
    if 1 <= class_check <= 126:
        return "255.0.0.0", "Class A"
    elif 128 <= class_check <= 191:
        return "255.255.0.0", "Class B"
    elif 192 <= class_check <= 223:
        return "255.255.255.0", "Class C"
    elif 224 <= class_check <= 239:
        return "255.0.0.0", "Class D"
    elif 240 <= class_check <= 254:
        return "255.0.0.0", "Class E"
    else:
        return None, "Invalid Class"
        
print("SUBNETTING AND SUBNET MASK")
IP = input("Enter the IP address : ")
pr = int(input("Enter the Prefix Length : "))

if is_valid_IPv4(IP):
    IP_compo = IP.split(".")
    check_class = int(IP_compo[0])
    
    mask, class_type = get_subnet_mask(check_class)
    
    if mask:
        print(f'{class_type} IP Address ')
        print("SUBNET MASK : ",mask)
        
    else:
        print("Invalid Class ")
        
else:
    print("Invalid IP Address ")
    
    
