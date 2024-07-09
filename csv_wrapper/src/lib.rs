extern crate libc;
extern crate csv;

use libc::c_char;
use std::ffi::{CStr, CString};
use std::ptr;
use std::os::raw::c_void;

#[no_mangle]
pub extern "C" fn read_csv(file_path: *const c_char) -> *const c_char {
    let c_str = unsafe { CStr::from_ptr(file_path) };
    let file_path_str = match c_str.to_str() {
        Ok(s) => s,
        Err(_) => return ptr::null(),
    };

    let mut rdr = match csv::Reader::from_path(file_path_str) {
        Ok(r) => r,
        Err(_) => return ptr::null(),
    };

    let mut result = String::new();
    for record in rdr.records() {
        match record {
            Ok(record) => {
                result.push_str(&format!("{:?}\n", record));
            }
            Err(_) => return ptr::null(),
        }
    }

    let c_string = CString::new(result).unwrap();
    c_string.into_raw()
}

#[no_mangle]
pub extern "C" fn free_string(s: *mut c_char) {
    if s.is_null() { return; }
    unsafe {
        CString::from_raw(s);
    }
}
