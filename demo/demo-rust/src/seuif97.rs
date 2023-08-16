extern crate libloading as lib;

fn resultpt(in1: f64, in2: f64, w: u32) -> Result<f64, Box<dyn std::error::Error>> {
    let lib = lib::Library::new("libseuif97")?;
    unsafe {
        let func: lib::Symbol<unsafe extern "C" fn(f64, f64, u32) -> f64> = lib.get(b"pt")?;
        Ok(func(in1, in2, w))
    }
}

pub fn pt(in1: f64, in2: f64, w: u32) -> f64 {
    let prop: f64 = match resultpt(in1, in2, w) {
        Ok(v) => v,
        Err(_e) => 1000.0,
    };
    prop
}
