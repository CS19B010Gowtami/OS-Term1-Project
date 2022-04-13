sudo adduser
if getent passwd $1; then
	echo user $1 created successfully
	mkdir "../admin/students/$1"
	touch "../admin/students/$1/details.txt"
	touch "../admin/students/$1/work.txt"
	cd "../admin/teachers/"
	for d in */ ; do
		touch "$d/$1.txt"
	done
	echo student files created
	cd "../.."
	chmod o= "admin/students/$1"
	chmod o= "admin/students/$1/work.txt"
	setfacl -m u:admin:rwx::allow "admin/students/$1"
	setfacl -m g:students:-::allow "admin/students/$1"
	setfacl -m g:teachers:x::allow "admin/students/$1"
	setfacl -m u:$1:x::allow "admin/students/$1"
	getfacl "admin/students/$1"
	setfacl -m u:admin:rwx::allow "admin/students/$1/work.txt"
	setfacl -m g:teachers:r::allow "admin/students/$1/work.txt"
	setfacl -m u:$1:rw::allow "admin/students/$1/work.txt"
	getfacl "admin/students/$1/work.txt"
	echo student subfolder permissions set
	cd "admin/teachers/"
	for d in */ ; do
		path=${d%/}
		echo $path
		echo path name $path
		touch "$path/$1.txt"
		chmod o= "$path/$1.txt"
		setfacl -m u:$1:r::allow "$path/$1.txt"
		setfacl -m u:$path:rw::allow "$path/$1.txt"
		setfacl -m u:admin:rwx::allow "$path/$1.txt"
		getfacl "$path/$1.txt"
	done
	echo teacher folder permissions set
	cd "../../"
else
	echo user $1 has not been created
fi
