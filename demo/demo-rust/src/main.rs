mod seuif97;
use seuif97::pt;

fn main() {
    let p: f64 = 16.0;
    let t: f64 = 535.9;
    let h: f64 = pt(p, t, 4);
    let s: f64 = pt(p, t, 5);
    println!("{p} {t} {h} {s}");
}
