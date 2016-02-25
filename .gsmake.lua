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
    };

    ["lime-simulator"] = {
        path            = "simulator";
        type            = function(task)
            local host = task.Owner.Loader.Config.TargetHost

            if host == "Windows" then
                return "win32"
            else
                return "exe"
            end
        end;
        dependencies    = { "lime" };
    };
}
