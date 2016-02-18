name "github.com/lemonkit/lime"

plugin "github.com/gsmake/clang"

plugin "github.com/gsmake/lua"



properties.lua = {
    dependencies        = {
        { name = "github.com/lemonkit/lemoon" };
    };
}


properties.clang = {
    ["lime"] = {
        type            = "static";
        dependencies    = {
            { name = "github.com/lemonkit/lemon" };
        };
    }
}
