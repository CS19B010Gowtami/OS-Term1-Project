
syscall:::entry
/
	uid == $1
/
{
	trace(execname);
	trace(arg0);
	@num[execname] = count();
	@num[(pid,execname)] = count();
}

syscall::open*:entry
/
	uid == $1
/
{
	/*printf("%s %s",execname,copyinstr(arg0));*/
	trace("execName is : ");
	trace(execname);
	trace("Arg0 is : ");
	trace(arg0);
}


syscall:::return
/
	uid == $1
/
{
	trace("Returning From Syscall");
	trace(execname);
	trace(arg0);
	@num[probefunc] = count();
}


proc:::exit
/
	uid == $1
/
{
        @[execname] = quantize(timestamp);
}
