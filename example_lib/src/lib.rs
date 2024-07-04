#[no_mangle]
pub extern "C" fn sort(arr: *mut i32, len: usize) {
    // 安全地访问原始指针指向的数组
    unsafe {
        if arr.is_null() {
            // 指针为null时不进行操作
            return;
        }
        let slice = std::slice::from_raw_parts_mut(arr, len);
        slice.sort_unstable();
    }
}
