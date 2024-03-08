#การแจ้งเตือนและ GUI ต่างๆ
import tkinter as tk
from tkinter import ttk
from tkinter import messagebox
# เวลา
import tkinter as tk
from datetime import datetime
#os ที่มีไว้สำหรับการทำงานกับระบบปฏิบัติการ (Operating System) โดยใช้ฟังก์ชันและเมทอดต่างๆ เพื่อจัดการไฟล์ระบบ โฟลเดอร์ การเข้าถึงสิทธิ์ของไฟล์
import os
#os.path.exists(): ใช้เพื่อตรวจสอบว่าไฟล์หรือโฟลเดอร์นั้นมีอยู่หรือไม่
#os.listdir(): ใช้เพื่อแสดงรายการของไฟล์และโฟลเดอร์ที่อยู่ในโฟลเดอร์ที่ระบุ
#os.mkdir(): ใช้สร้างโฟลเดอร์ใหม่
#os.remove(): ใช้ลบไฟล์
#os.rename(): ใช้เปลี่ยนชื่อของไฟล์หรือโฟลเดอร์
#os.chdir(): ใช้เปลี่ยนโดยตรงไปยังโฟลเดอร์ที่กำหนด
cound = 0

# ฟังก์ชันสำหรับเพิ่มข้อมูล-------------------
def in_employee(employee_id_entry):
    # เก็บค่าเวลาเพื่อนำไปเซ็คค่า
    current_time = datetime.now().time()
    start_time = datetime.strptime("08:00:00", "%H:%M:%S").time()
    end_time = datetime.strptime("16:00:00", "%H:%M:%S").time()
    # หาพนักงาน
    found_employee = find_employee(employee_id_entry)
    if found_employee:
        employee_id, name = found_employee  # สร้างตัวแปรจากข้อมูลพนักงานที่ค้นพบ
        # สร้างเวลาเพื่อบันทึกเวลลาปัจจุบัน
        time = datetime.now()
        formatted_time = time.strftime("%H:%M:%S, %d/%m/%Y")

        if start_time >= current_time:  # บันทึกในเข้างานตรงเวลา
            status = "Attend work"
            with open("inwork.txt", "a", encoding="utf-8") as file:
                file.write(f"  {employee_id}   |   {name}  |   {status}    |   {formatted_time}    \n")
            messagebox.showinfo("Success", "ข้อมูลคนเข้างานถูกเพิ่มแล้ว")

        elif start_time < current_time <= end_time:  # บันทึกในเข้างานสาย
            status = "Late for work"
            with open("latwork.txt", "a", encoding="utf-8") as file:
                file.write(f"  {employee_id}   |   {name}  |   {status}    |   {formatted_time}    \n")
            messagebox.showinfo("Success", "คุณเข้างานสาย")
        else:
            messagebox.showerror("Error", "ไม่สามารถบันทึกเวลาเข้างานได้")
    else:
        messagebox.showerror("Error", "ไม่พบข้อมูลพนักงาน")

#ออกงาน-----------------------------------------------
def out_employee(employee_id_entry):
    #เก็บค่าเวลาเพื่อนำไปเซ็คค่า
    current_time = datetime.now().time()
    end_time = datetime.strptime("16:00:00", "%H:%M:%S").time()
    #หาพนักงาน
    found_employee = find_employee(employee_id_entry)
    if found_employee:
        employee_id, name = found_employee  # สร้างตัวแปรจากข้อมูลพนักงานที่ค้นพบ
        #สร้างเวลาเพื่อบันทึกเวลลาปัจจุบัน----
        time = datetime.now()
        formatted_time = time.strftime("%H:%M:%S, %d/%m/%Y")
        #-----------------------------
        if end_time > current_time : #ออกก่อนเวลา
            status = "Leave work early"
            with open("outwork.txt", "a", encoding="utf-8") as file:
                file.write(f"  {employee_id}   |   {name}  |   {status}    |   {formatted_time}    \n")
            messagebox.showinfo("Success", "ข้อมูลคนออกงานถูกเพิ่มแล้ว")
        else :
            status = "out to work"
            with open("outwork.txt", "a", encoding="utf-8") as file:
                file.write(f"  {employee_id}   |   {name}  |   {status}    |   {formatted_time}    \n")
            messagebox.showinfo("Success", "ข้อมูลคนออกงานถูกเพิ่มแล้ว")
    else:
        messagebox.showerror("Error", "ไม่พบข้อมูลพนักงาน")
#ค้นหา---------------------------------
def find_employee(employee_id_entry):
    employee_id = employee_id_entry.get()
    found_employee = None
    file_path = "employee_data.txt"

    if os.path.isfile(file_path):
        with open(file_path, "r") as file:
            for line in file:
                data = line.strip().split("|")
                if data[0].strip() == employee_id:
                    found_employee = data[0].strip(), data[1].strip()  # รับรหัสและชื่อพนักงาน
                    break
    else:
        messagebox.showerror("Error", "ไม่พบไฟล์ที่ระบุ คุณอาจจะต้องเพิ่มข้อมูลก่อน")
        
    return found_employee

# ฟังก์ชันสำหรับเพิ่มข้อมูล
def add_employee(employee_id_entry, name_employee):
    #หาพนักงาน
    found_employee = find_employee(employee_id_entry)
    if found_employee == None:
        employee_id = employee_id_entry.get()
        name = name_employee.get()
        if name == "" or employee_id == "":
            messagebox.showerror("Error", "ใส่ข้อมูลให้ครบ")
        else:
            with open("employee_data.txt", "a", encoding="utf-8") as file:
                file.write(f"  {employee_id}   |   {name}  \n")
            messagebox.showinfo("Success", "ข้อมูลถูกเพิ่มแล้ว กรุณตรจสอบอีกครั้ง")
    else:
        messagebox.showerror("Error", "รหัสที่คุณใช้มีอยู่แล้ว")

# ฟังก์ชันสำหรับแก้ไขข้อมูล
def edit_employee(id_entry, name_entry):
    employee_id = id_entry.get()
    new_name = name_entry.get()
    lines = []
    found = False  # เพิ่มตัวแปรเพื่อตรวจสอบว่าพบข้อมูลหรือไม่
    file_path = "employee_data.txt"
    if os.path.isfile(file_path):
        with open(file_path, "r") as file:
            lines = file.readlines()
        with open(file_path, "w") as file:
            for line in lines:
                data = line.strip().split("|")
                if data[0].strip() == employee_id:
                    found = True  # พบข้อมูล
                    file.write(f" {employee_id} | {new_name} \n")
                else:
                    file.write(line)
        if found:
            messagebox.showinfo("Success", "ข้อมูลชื่อพนักงานถูกแก้ไขแล้ว")
        else:
            messagebox.showerror("Error", "ไม่พบข้อมูลชื่อพนักงาน")
    else:
        messagebox.showerror("Error", "ไม่พบไฟล์ที่ระบุ คุณอาจจะต้องเพิ่มข้อมูลก่อน")

# ฟังก์ชันสำหรับลบข้อมูล
def delete_employee(employee_id_entry):
    employee_id = employee_id_entry.get()
    lines = []
    found = False  # เพิ่มตัวแปรเพื่อตรวจสอบว่าพบข้อมูลหรือไม่
    file_path = "employee_data.txt"
    if os.path.isfile(file_path):
        with open(file_path, "r") as file:
            lines = file.readlines()
        with open(file_path, "w") as file:
            for line in lines:
                data = line.strip().split("|")
                if data[0].strip() == employee_id:
                    found = True  # พบข้อมูล
                else:
                    file.write(line)
        if found:
            messagebox.showinfo("Success", "ข้อมูลชื่อพนักงานถูกลบแล้ว")
        else:
            messagebox.showerror("Error", "ไม่พบข้อมูลชื่อพนักงาน")
    else:
        messagebox.showerror("Error", "ไม่พบไฟล์ที่ระบุ อาจจะไม่มีพนักงานเหลือแล้วก็ได้นะ")

# แสดงข้อมูล---------------------------------------------------------
def show_employee_data():
    file_path = "employee_data.txt"
    if os.path.isfile(file_path):
        # Read data from the file
        with open(file_path, "r", encoding="utf-8") as file:
            lines = file.readlines()
        
        # Create a new window to display the data
        show_data_window = tk.Toplevel(root)
        show_data_window.title("ข้อมูลพนักงาน")
        
        # Create a treeview to display the data as a table
        tree = ttk.Treeview(show_data_window, columns=("ID", "Name"), show="headings")
        tree.heading("ID", text="รหัสพนักงาน")
        tree.heading("Name", text="ชื่อ-สกุล")
        
        # Set column widths
        tree.column("ID", width=200, anchor="center")
        tree.column("Name", width=100, anchor="center")
        
        for line in lines:
            data = line.strip().split("|")
            
            tree.insert("", "end", values=data)
            
        
        tree.pack(fill="both", expand=True)
    else:
        messagebox.showerror("Error", "ไม่พบไฟล์ที่ระบุ")

def show_inwork_data():
    file_path = "inwork.txt"
    if os.path.isfile(file_path):
        # Read data from the file
        with open(file_path, "r", encoding="utf-8") as file:
            lines = file.readlines()
        
        # Create a new window to display the data
        show_data_window = tk.Toplevel(root)
        show_data_window.title("ข้อมูลการเข้างาน")
        
        # Create a treeview to display the data as a table
        tree = ttk.Treeview(show_data_window, columns=("ID", "Name", "Status", "Time"), show="headings")
        tree.heading("ID", text="รหัสพนักงาน")
        tree.heading("Name", text="ชื่อ-สกุล")
        tree.heading("Status", text="สถานะ")
        tree.heading("Time", text="เวลา")
        
        # Set column widths
        tree.column("ID", width=100, anchor="center")
        tree.column("Name", width=100, anchor="center")
        tree.column("Status", width=100, anchor="center")
        tree.column("Time", width=150, anchor="center")
        
        # Create a dictionary to store the latest record of each employee
        latest_records = {}
        for line in lines:
            data = line.strip().split("|")
            employee_id = data[0].strip()
            latest_records[employee_id] = data
        
        # Insert data into the treeview
        for record in latest_records.values():
            tree.insert("", "end", values=record)
            
        tree.pack(fill="both", expand=True)
    else:
        messagebox.showerror("Error", "ไม่พบไฟล์ที่ระบุ")

def show_latwork_data():
    file_path = "latwork.txt"
    if os.path.isfile(file_path):
        # Read data from the file
        with open(file_path, "r", encoding="utf-8") as file:
            lines = file.readlines()
        
        # Create a new window to display the data
        show_data_window = tk.Toplevel(root)
        show_data_window.title("ข้อมูลการเข้างานสาย")
        
        # Create a treeview to display the data as a table
        tree = ttk.Treeview(show_data_window, columns=("ID", "Name", "Status", "Time"), show="headings")
        tree.heading("ID", text="รหัสพนักงาน")
        tree.heading("Name", text="ชื่อ-สกุล")
        tree.heading("Status", text="สถานะ")
        tree.heading("Time", text="เวลา")
        
        # Set column widths
        tree.column("ID", width=100, anchor="center")
        tree.column("Name", width=100, anchor="center")
        tree.column("Status", width=100, anchor="center")
        tree.column("Time", width=150, anchor="center")
        
        # Create a dictionary to store the latest record of each employee
        latest_records = {}
        for line in lines:
            data = line.strip().split("|")
            employee_id = data[0].strip()
            latest_records[employee_id] = data
        
        # Insert data into the treeview
        for record in latest_records.values():
            tree.insert("", "end", values=record)
            
        tree.pack(fill="both", expand=True)
    else:
        messagebox.showerror("Error", "ไม่พบไฟล์ที่ระบุ")

def show_outwork_data():
    file_path = "outwork.txt"
    if os.path.isfile(file_path):
        # Read data from the file
        with open(file_path, "r", encoding="utf-8") as file:
            lines = file.readlines()
        
        # Create a new window to display the data
        show_data_window = tk.Toplevel(root)
        show_data_window.title("ข้อมูลการออกงาน")
        
        # Create a treeview to display the data as a table
        tree = ttk.Treeview(show_data_window, columns=("ID", "Name", "Status", "Time"), show="headings")
        tree.heading("ID", text="รหัสพนักงาน")
        tree.heading("Name", text="ชื่อ-สกุล")
        tree.heading("Status", text="สถานะ")
        tree.heading("Time", text="เวลา")
        
        # Set column widths
        tree.column("ID", width=100, anchor="center")
        tree.column("Name", width=100, anchor="center")
        tree.column("Status", width=100, anchor="center")
        tree.column("Time", width=150, anchor="center")
        
        # Create a dictionary to store the latest record of each employee
        latest_records = {}
        for line in lines:
            data = line.strip().split("|")
            employee_id = data[0].strip()
            latest_records[employee_id] = data
        
        # Insert data into the treeview
        for record in latest_records.values():
            tree.insert("", "end", values=record)
            
        tree.pack(fill="both", expand=True)
    else:
        messagebox.showerror("Error", "ไม่พบไฟล์ที่ระบุ")

    

#นาฬิกา-------------------------------------------------------------
def update_clock():
    current_time = datetime.now().strftime("%H:%M:%S")
    clock_label.config(text=current_time)
    root.after(1000, update_clock)

#เวลา--------------------------------------------------------------
def update_date():
    current_date = datetime.now().strftime("%d/%m/%Y")
    date_label.config(text=current_date)
    root.after(1000, update_date)

# สร้างหน้า GUI หน้าที่ 1: จัดการข้อมูล
def edit_page():
    add_page = tk.Toplevel(root)
    add_page.title("จัดการข้อมูล")
    add_page.geometry("320x180+200+100")

    tk.Label(add_page, text="กรุณกรอกรหัส Admin", font=("Arial", 12)).grid(row=0, column=0, columnspan=3, padx=10, pady=5)
    admin_id_entry = tk.Entry(add_page, font=("Arial", 12))
    admin_id_entry.grid(row=1, column=0, columnspan=3, padx=10, pady=5)

    tk.Label(add_page, text="รหัส").grid(row=2, column=0)
    tk.Label(add_page, text="ชื่อ").grid(row=3, column=0)

    id_entry = tk.Entry(add_page)
    name_entry = tk.Entry(add_page)

    id_entry.grid(row=2, column=1)
    name_entry.grid(row=3, column=1)

    def validate_admin_add(cound):
        admin_id = admin_id_entry.get()
        # ตรวจสอบว่ารหัส Admin ถูกต้องหรือไม่
        if admin_id == "1234":  # แทน your_admin_id_here ด้วยรหัส Admin ที่คุณกำหนด
            if cound == 1:
                add_employee(id_entry, name_entry)
            elif cound == 2:
                edit_employee(id_entry, name_entry)
            elif cound == 3:
                delete_employee(id_entry)
            else :
                messagebox.showerror("Error", "Error ผิดที่ cound แน่ๆ")
        else:
            messagebox.showerror("Error", "รหัส Admin ไม่ถูกต้อง")

    edit_button = tk.Button(add_page, text="เพิ่มข้อมูล", command=lambda: validate_admin_add(cound = 1))
    edit_button.configure(font=("Arial", 9), width=10, height=2)
    edit_button.grid(row=4, column=0, padx=10, pady=5)

    edit_button = tk.Button(add_page, text="แก้ไขชื่อ", command=lambda: validate_admin_add(cound = 2))
    edit_button.configure(font=("Arial", 9), width=10, height=2)
    edit_button.grid(row=4, column=1, padx=10, pady=5)

    delete_button = tk.Button(add_page, text="ลบข้อมูล", command=lambda: validate_admin_add(cound = 3))
    delete_button.configure(font=("Arial", 9), width=10, height=2)
    delete_button.grid(row=4, column=2, padx=10, pady=5)

def show_page():
    show_page = tk.Toplevel(root)
    show_page.title("แสดงข้อมูล")
    show_page.geometry("170x220+200+100")

    show_employee_data_button = tk.Button(show_page, text="แสดงข้อมูลพนักงาน", command=show_employee_data)
    show_employee_data_button.configure(font=("Arial", 9), width=20, height=2)
    show_employee_data_button.grid(row=0, column=0, padx=10, pady=5)

    show_inwork_data_button = tk.Button(show_page, text="แสดงข้อมูลเข้างาน", command=show_inwork_data)
    show_inwork_data_button.configure(font=("Arial", 9), width=20, height=2)
    show_inwork_data_button.grid(row=1, column=0, padx=10, pady=5)

    show_latwork_data_button = tk.Button(show_page, text="แสดงข้อมูลเข้างานสาย", command=show_latwork_data)
    show_latwork_data_button.configure(font=("Arial", 9), width=20, height=2)
    show_latwork_data_button.grid(row=2, column=0, padx=10, pady=5)

    show_outwork_data_button = tk.Button(show_page, text="แสดงข้อมูลออกงาน", command=show_outwork_data)
    show_outwork_data_button.configure(font=("Arial", 9), width=20, height=2)
    show_outwork_data_button.grid(row=3, column=0, padx=10, pady=5)



# สร้างหน้า GUI หน้าหลัก--------------------------------------------------------------------------------------------
root = tk.Tk()
root.title("ระบบจัดการข้อมูลระบบคนเข้า-ออกงาน")

# กำหนดขนาดของหน้าต่าง (ความกว้าง x ความสูง + ตำแหน่ง x ตำแหน่ง y)
root.geometry("435x265+200+100")

# นาฬิกา
clock_label = tk.Label(root, font=("Arial", 36))
clock_label.grid(row=1, column=1, columnspan=2, padx=20, pady=20)  # จัดวางในแถวที่ 0, คอลัมน์ที่ 0 และเหลือทั้งแถว
update_clock()

#เวลา 
date_label = tk.Label(root, font=("Arial", 12))
date_label.grid(row=0, column=1, columnspan=2, padx=10, pady=10)  # จัดวางในแถวที่ 1, คอลัมน์ที่ 1 และเหลือทั้งแถว
update_date()

# กรอกรหัสพนักงาน
tk.Label(root, text="กรอกรหัสพนักงาน", font=("Arial", 12)).grid(row=2, column=1, columnspan=2, padx=10, pady=5)  # จัดวางในแถวที่ 1, คอลัมน์ที่ 0
employee_id_entry = tk.Entry(root, font=("Arial", 12))
employee_id_entry.grid(row=3, column=1, columnspan=2, padx=10, pady=5)  # จัดวางในแถวที่ 1, คอลัมน์ที่ 1

# ปุ่มเพิ่มเวลาเข้า
add_page_button = tk.Button(root, text="เข้างาน", command=lambda: in_employee(employee_id_entry))
add_page_button.configure(font=("Arial", 9), width=10, height=2)
add_page_button.grid(row=4, column=0, padx=10, pady=5)  # จัดวางในแถวที่ 2, คอลัมน์ที่ 0
# ปุ่มเพิ่มเวลาออก
edit_page_button = tk.Button(root, text="ออกงาน", command=lambda: out_employee(employee_id_entry))
edit_page_button.configure(font=("Arial", 9), width=10, height=2)
edit_page_button.grid(row=4, column=1, padx=10, pady=5)  # จัดวางในแถวที่ 2, คอลัมน์ที่ 1
# ปุ่มเพิ่มเวลาแก้ไข
delete_page_button = tk.Button(root, text="จัดการข้อมูล", command=edit_page)
delete_page_button.configure(font=("Arial", 9), width=10, height=2)
delete_page_button.grid(row=4, column=2, padx=10, pady=5)  # จัดวางในแถวที่ 3, คอลัมน์ที่ 0
# ปุ่มเพิ่มเวลาแสดง
show_data_button = tk.Button(root, text="แสดงข้อมูล", command=show_page)
show_data_button.configure(font=("Arial", 9), width=10, height=2)
show_data_button.grid(row=4, column=3, padx=10, pady=5)  # จัดวางในแถวที่ 3, คอลัมน์ที่ 1

root.mainloop()