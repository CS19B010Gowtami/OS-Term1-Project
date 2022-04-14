sudo adduser
if getent passwd $1; then
	echo user $1 created successfully\n
	mkdir "../admin/teachers/$1"
	chmod go= "../admin/teachers/$1"
	setfacl -m u:admin:rwx::allow "../admin/teachers/$1"
	setfacl -m g:students:x::allow "../admin/teachers/$1"
	setfacl -m u:$1:x::allow "../admin/teachers/$1"
	getfacl "../admin/teachers/$1"
	cd "../admin/teachers/pid0"
	for FILE in * ; do
		touch "../$1/$FILE"
		chmod go= "../$1/$FILE"
		setfacl -m u:admin:rwx::allow "../$1/$FILE"
		setfacl -m u:${FILE%.*}:r::allow "../$1/$FILE"
		setfacl -m u:$1:rw::allow "../$1/$FILE"
		getfacl "../$1/$FILE"
	done
else
	echo user has not been created
fi
