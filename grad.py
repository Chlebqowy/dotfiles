def calc_grad(color1: int, color2: int, percent: int) -> str:
    c1 = [
        (color1>>16)&(256-1), 
        (color1>>8)&(256-1), 
        color1&(256-1)]
    c2 = [
        (color2>>16)&(256-1), 
        (color2>>8)&(256-1), 
        color2&(256-1)]
    diff = [c1[0]-c2[0], c1[1]-c2[1], c1[2]-c2[2]]
    diff_grad = [(diff[0]*percent)//100, (diff[1]*percent)//100, (diff[2]*percent)//100]
    grad = [c1[0] - diff_grad[0], c1[1] - diff_grad[1], c1[2] - diff_grad[2]]
    grad_hex = ["", "", ""]
    #print(grad)
    grad_hex[0] = hex(grad[0])[2:]
    grad_hex[1] = hex(grad[1])[2:]
    grad_hex[2] = hex(grad[2])[2:]
    #print(grad_hex)
    grad_hex_str = "#"
    for i in grad_hex: 
        if len(i) == 1:
            i = "0" + i
        grad_hex_str += i
    return grad_hex_str
# Use with python command and import grad
