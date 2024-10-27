import os

# 获取当前目录路径
current_dir = os.getcwd()

# 遍历当前目录中的所有文件
for filename in os.listdir(current_dir):
    # 检查是否是文件（而不是目录）
    if os.path.isfile(os.path.join(current_dir, filename)):
        # 新文件名加上前缀
        new_filename = "leetcode_" + filename
        # 获取旧文件的完整路径
        old_file = os.path.join(current_dir, filename)
        # 获取新文件的完整路径
        new_file = os.path.join(current_dir, new_filename)
        # 重命名文件
        os.rename(old_file, new_file)

print("所有文件名前已成功添加前缀 'leetcode_'")
