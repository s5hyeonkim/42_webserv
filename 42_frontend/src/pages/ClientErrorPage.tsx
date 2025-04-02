import { useEffect } from "react";
import { Outlet } from "react-router-dom";

const ClientErrorPage = () => {
  console.log("client error page");

  useEffect(() => {
    const preventBack = (e: BeforeUnloadEvent) => {
      e.preventDefault();
      // e.returnValue = '';
    };
    const handlePopState = () => {
      window.history.pushState(null, "", window.location.href);
    };
    window.history.pushState(null, "", window.location.href);
    window.addEventListener("popstate", handlePopState);
    window.addEventListener("beforeunload", preventBack);
    return () => {
      window.removeEventListener("popstate", handlePopState);
      window.removeEventListener("beforeunload", preventBack);
    };
  });
  return (
    <div>
      <Outlet />
      <div>ErrorPage: status 40x</div>
    </div>
  );
};

export default ClientErrorPage;
